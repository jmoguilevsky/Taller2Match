//
// Created by chris on 16/04/16.
//

#include "Server.h"
#include "utils.h"
#include <stdio.h>

std::string Server::sharedAddress;
struct mg_mgr Server::mgr;
struct mg_connection *Server::listeningConnection;
std::vector<ClientHandler*> Server::cHandlers;
bool Server::CONTINUE;

// Constants

static const char* ECHOURI = "/echo/";

static std::string echo(struct mg_connection *connectionToClient, struct http_message* httpMessage) {

	char message[256];
	mg_get_http_var(&httpMessage->body, "message", message, sizeof(message));

	return "{ echo: \"" + std::string(message) +"\" }";
}


// Private Function.
// Returns a std::string that represents the answer from the request.
static std::string interpretRequest(struct mg_connection *connectionToClient, void* eventHandlerData) {

	struct http_message* httpMessage = (http_message*) eventHandlerData;

	if (mg_vcmp(&httpMessage->uri, ECHOURI) == 0) {
		return echo(connectionToClient, httpMessage);
	}

	return "{}";
}


// Private Function.
// Sends a @reply to a @connectionToClient entirely.
static void sendWholeReply(struct mg_connection* connectionToClient, std::string& reply) {
	mg_printf(connectionToClient, "HTTP/1.1 200 OK\r\n"
			"Content-Type: application/json\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
			"%s", (int) strlen(reply.c_str()), reply.c_str());

}

void Server::clientHandler(struct mg_connection *connectionToClient, int ev,
                           void *p) {
	if (connectionToClient->user_data == NULL) {
		// Recién se creó la conexión. La linkeo al su ClientHandler.
		std::cout << "connecting!" << std::endl;
		connectionToClient->user_data = (void *) new ClientHandler(
				connectionToClient, sharedAddress);
		// Podríamos agregarla a un map o algo así si hace falta
		// Pero hay que acordarse de sacarla del map cuando se cierra
		// la conexión.
	}
	ClientHandler *handler = ((ClientHandler *) connectionToClient->user_data);

    if (ev == MG_EV_HTTP_REQUEST) {

		std::cout << "Interpretando request" << std::endl;

		std::string reply = interpretRequest(connectionToClient, p);
		sendWholeReply(connectionToClient, reply);
	}

	if (ev == MG_EV_CLOSE) {
		// Cuando se cierra la conexión, libero el ClientHandler.
		// Borrar del map.
		std::cout << "closing connection" << std::endl;;
		delete handler;
		return;
	}

	/*if(ev == MG_EV_RECV) {
		std::cout << "sending request to client handler" << std::endl;
		handler->handle(connectionToClient, ev);
	}*/
}


void Server::stop() {
	CONTINUE = false;
}

void Server::init(const std::string &port, const std::string &sharedAddress) {
	Server::sharedAddress = sharedAddress;
	mg_mgr_init(&mgr, NULL);
	listeningConnection = mg_bind(&mgr, port.c_str(), clientHandler);
	mg_enable_multithreading(listeningConnection);
	mg_set_protocol_http_websocket(listeningConnection);
	CONTINUE = true;
	while (CONTINUE) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
}

