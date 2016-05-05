//
// Created by chris on 23/04/16.
//

#include "MgHTTPClient.h"
#include "MgConnectionManager.h"
#include <iostream>

HTTPResponse MgHTTPClient::sendRequest(HTTPRequest request) {
	if (!request.isEmpty()) {
		mg_printf(c, "%s", request.toCString());
		waiting = true;
		while (waiting) {
			mgr.poll(1000);
		}
	}
	return response;
}

void MgHTTPClient::handle(mg_connection *c, int ev, void *p) {
	if (ev == MG_EV_HTTP_REPLY) {
		struct http_message *hm = (struct http_message *) p;
		response = HTTPResponse(hm); //TODO No queda bien esto.
		c->flags |= MG_F_CLOSE_IMMEDIATELY;
		waiting = false;
	}
}

void MgHTTPClient::eventHandler(mg_connection *c, int ev,
                                void *p) {
	MgHTTPClient *connectionToShared = (MgHTTPClient *) c->user_data;
	connectionToShared->handle(c, ev, p);
}

bool MgHTTPClient::connectToUrl(std::string url) {
	if (c != NULL) return false;
	c = mgr.configureOutboundConnection(url, this, eventHandler);
	return c != NULL;
}

