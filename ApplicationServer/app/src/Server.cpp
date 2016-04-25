//
// Created by chris on 16/04/16.
//

#include "Server.h"
#include "Handlers/Login.h"
#include "Handlers/SignUp.h"

//std::string Server::sharedAddress;

RequestHandler *Server::getRequestHandler(HTTPRequest request) {
	// TODO esto puede/debe estar fuera de la clase Server
	// Recibe un mensaje del cliente, y devuelve el request handler para eso.
	// return RequestHandler(request,dbManager);
	if (request.getVerb() == "POST" && request.getUri() == "/login") {
		return new Login(request, db);
	}
	if (request.getVerb() == "POST" && request.getUri() == "/signup") {
		return new SignUp(request, db);
	}

}

void Server::clientHandler(struct mg_connection *c, int ev, void *p) {
	if (ev == MG_EV_HTTP_REQUEST) {
		HTTPRequest request((struct http_message *) p);
		Server *server = (Server *) c->user_data;
		RequestHandler *handler = server->getRequestHandler(request);
		HTTPResponse response = handler->handle();
		std::cout << "Response:\n" << response.toCString() << std::endl;
		mg_printf(c, "%s\r\n", response.toCString());
		c->flags |= MG_F_SEND_AND_CLOSE;
	}
}


void Server::stop() {
	CONTINUE = false;
}

Server::Server(std::string port, std::string sharedAddress) : db("login") {
	// TODO
	this->sharedAddress = sharedAddress;
	this->port = port;
	mg_mgr_init(&mgr, NULL);
	struct mg_bind_opts opts;
	opts.user_data = (void *) this;
	listeningConnection = mg_bind_opt(&mgr, port.c_str(), clientHandler, opts);
	mg_enable_multithreading(listeningConnection);
	mg_set_protocol_http_websocket(listeningConnection);
}

void Server::start() {

	CONTINUE = true;
	while (CONTINUE) {
		mg_mgr_poll(&mgr, 1000);
	}
}

Server::~Server() {
	mg_mgr_free(&mgr);
}