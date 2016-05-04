#include "Server.h"

RequestHandler *Server::getRequestHandler(HTTPRequest request) {
	return handlerSelector.getRequestHandler(request);
}

// TODO: Eliminar este handler, que sea un método de un objeto que se dedique a manejar requests
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

Server::Server(std::string port, std::string sharedAddress) : 	handlerSelector(sharedAddress),
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