#include "MgServer.h"


// TODO: Eliminar este handler, que sea un método de un objeto que se dedique a manejar requests

void MgServer::clientHandler(struct mg_connection *c, int ev, void *p) {
	if (ev == MG_EV_HTTP_REQUEST) {
		HTTPRequest request((struct http_message *) p);
		MgServer *thisServer = (MgServer *) c->user_data;
		Handler *handler = thisServer->handlerSelector.getRequestHandler(
				request);
		HTTPResponse response = handler->handle();
		std::cout << "\nResponse:\n" << response.toCString() << std::endl;
		mg_printf(c, "%s\r\n", response.toCString());
		c->flags |= MG_F_SEND_AND_CLOSE;
		delete handler;
	}
}

void MgServer::stop() {
	this->isServerUP = false;
}

MgServer::MgServer(std::string port, HandlerSelector &handlerSelector)
		: handlerSelector(handlerSelector) {

	// TODO Poner esto en un método "init", para poder devolver OK o ERROR si falla la conexión.
	mongooseConnectionManager.configureListeningConnection(port, this, this->clientHandler);
}

void MgServer::start() {

	this->isServerUP = true;
	while (isServerUP) {
		mongooseConnectionManager.poll(1000);
	}
}

MgServer::~MgServer() {
}