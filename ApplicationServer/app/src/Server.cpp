//
// Created by chris on 16/04/16.
//

#include "Server.h"
#include "utils.h"

std::string Server::sharedAddress;
struct mg_mgr Server::mgr;
struct mg_connection *Server::listeningConnection;
std::vector<ClientHandler*> Server::cHandlers;
bool Server::CONTINUE;

void Server::clientHandler(struct mg_connection *connectionToClient, int ev,
                           void *p) {
	if (connectionToClient->user_data == NULL) {
		// Recién se creó la conexión. La linkeo al su ClientHandler.
		connectionToClient->user_data = (void *) new ClientHandler(
				connectionToClient, sharedAddress);
		// Podríamos agregarla a un map o algo así si hace falta
		// Pero hay que acordarse de sacarla del map cuando se cierra
		// la conexión.
	}
	ClientHandler *handler = ((ClientHandler *) connectionToClient->user_data);
	if (ev == MG_EV_CLOSE) {
		// Cuando se cierra la conexión, libero el ClientHandler.
		// Borrar del map.
		delete handler;
		return;
	}
	handler->handle(connectionToClient, ev);
}


void Server::stop() {
	CONTINUE = false;
}

void Server::init(const std::string &port, const std::string &sharedAddress) {
	Server::sharedAddress = sharedAddress;
	mg_mgr_init(&mgr, NULL);
	listeningConnection = mg_bind(&mgr, port.c_str(), clientHandler);
	//mg_set_protocol_http_websocket(listeningConnection);
	CONTINUE = true;
	while (CONTINUE) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
}

