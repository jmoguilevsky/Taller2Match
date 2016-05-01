//
// Created by chris on 23/04/16.
//

#include "HTTPRequestSender.h"
#include <iostream>

HTTPRequestSender::HTTPRequestSender(std::string address) {
	this->address = address;
}

HTTPResponse HTTPRequestSender::sendRequest(HTTPRequest request) {
	if (!request.isEmpty()) {
		mg_mgr_init(&mgr, NULL);
		c = mg_connect(&mgr, address.c_str(), eventHandler);
		// CHEQUEAR SI SE CONECTA O NO
		c->user_data = (void *) this;
		mg_set_protocol_http_websocket(c);
		std::cout << "Request:\n" << request.toCString() << std::endl;
		mg_printf(c, "%s", request.toCString());
		waiting = true;
		while (waiting) {
			mg_mgr_poll(&mgr, 1000);
		}
		mg_mgr_free(&mgr);
	}
	return response;
}

void HTTPRequestSender::handle(mg_connection *pConnection, int ev, void *p) {
	if (ev == MG_EV_HTTP_REPLY) {
		struct http_message *hm = (struct http_message *) p;
		response = HTTPResponse(hm); //TODO No queda bien esto.
		pConnection->flags |= MG_F_CLOSE_IMMEDIATELY;
		waiting = false;
	}
}

void HTTPRequestSender::eventHandler(struct mg_connection *c, int ev,
                                     void *p) {
	HTTPRequestSender *connectionToShared = (HTTPRequestSender *) c->user_data;
	connectionToShared->handle(c, ev, p);
}