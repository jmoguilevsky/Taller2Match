#include "Server.h"
#include "Handlers/Login.h"
#include "Handlers/SignUp.h"
#include "Handlers/Matcher.h"
#include "Handlers/AuthenticationError.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define URI_LOGIN "/login"
#define URI_SIGNUP "/signup"
#define URI_CANDIDATES "/candidates"
#define ID_TOKEN "token"
#define ID_EMAIL "email"

RequestHandler *Server::getRequestHandler(HTTPRequest request) {
	// TODO esto puede/debe estar fuera de la clase Server
	// Recibe un mensaje del cliente, y devuelve el request handler para eso.
	// return RequestHandler(request,dbManager);
	if (request.getVerb() == HTTP_POST && request.getUri() == URI_LOGIN) {
		// Acá como es login, no hay que verificar el token y la autenticación.
		return new Login(request, db, tokenManager, sharedServer);
	}
	//TODO En el resto de los requests, hay que verificar que el token sea válido.
	//TODO Si es inválido -> ERROR!. Si es válido, sigo.

	if (request.getVerb() == HTTP_POST && request.getUri() == URI_SIGNUP) {
		return new SignUp(request, db);
	}

	Json::Value authorization = utils::stringToJson(
			request.getHeader("Authorization"));
	std::string username = authorization[ID_EMAIL].asString();
	std::string token = authorization[ID_TOKEN].asString();
	if (!tokenManager.isValid(username, token)) {
		return new AuthenticationError(request);
	}

	if (request.getVerb() == HTTP_GET && request.getUri() == URI_CANDIDATES) {
		return new Matcher(request, matchesDB, sharedServer);
	}

}

void Server::clientHandler(struct mg_connection *c, int ev, void *p) {
	if (ev == MG_EV_HTTP_REQUEST) {
		HTTPRequest request((struct http_message *) p);
		Server *thisServer = (Server *) c->user_data;
		RequestHandler *handler = thisServer->getRequestHandler(request);
		HTTPResponse response = handler->handle();
		std::cout << "\nResponse:\n" << response.toCString() << std::endl;
		mg_printf(c, "%s\r\n", response.toCString());
		c->flags |= MG_F_SEND_AND_CLOSE;
		delete handler;
	}
}


void Server::stop() {
	this->isServerUP = false;
}

Server::Server(std::string port, std::string sharedAddress) : db("login"),
                                                              sharedServer(sharedAddress) {
	mongooseConnectionManager.initManager();
	mongooseConnectionManager.configureConnection(port, this);
}

void Server::start() {

	this->isServerUP = true;
	while (isServerUP) {
		mongooseConnectionManager.checkForRequests(1000);
	}
}

Server::~Server() {
	mongooseConnectionManager.deleteManager();
}