#include "MgServer.h"


// TODO: Eliminar este handler, que sea un método de un objeto que se dedique a manejar requests

void MgServer::clientHandler(struct mg_connection *c, int ev, void *p) {
	if (ev == MG_EV_HTTP_REQUEST) {


		HTTPRequest request((struct http_message *) p);
		MgServer *thisServer = (MgServer *) c->user_data;

		HTTPResponse response = thisServer->requestHandler.handle(
				request);
		std::cout << "RESPONSE CODE: " << response.getCode() << std::endl;
		std::cout << "RESPONSE Body: " << response.getBody() << std::endl;
		mg_printf(c, "%s\r\n", response.toCString());
		c->flags |= MG_F_SEND_AND_CLOSE;
	}
}



void MgServer::stop() {
	this->isServerUP = false;
}

MgServer::MgServer(std::string port, RequestHandler &requestHandler)
		: requestHandler(requestHandler) {

	// TODO Poner esto en un método "init", para poder devolver OK o ERROR si falla la conexión.
	c = mongooseConnectionManager.configureListeningConnection(port, this, this->clientHandler);
}

void MgServer::start() {

	this->isServerUP = true;
	while (isServerUP) {
		mongooseConnectionManager.poll(1000);
	}
}

MgServer::~MgServer() {
}