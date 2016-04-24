//
// Created by chris on 23/04/16.
//

#ifndef APPSERVER_CONNECTIONTOSHARED_H
#define APPSERVER_CONNECTIONTOSHARED_H

#include "HTTPRequest.h"
#include "mongoose-master/mongoose.h"

class ConnectionToShared {

	struct mg_mgr mgr;
	struct mg_connection *c;
	HTTPRequest response;
	bool waiting;

public:
	ConnectionToShared(std::string sharedAddress);

	HTTPRequest sendRequest(HTTPRequest request);

	void handle(mg_connection *pConnection, int ev, void *p);

	static void sharedHandler(struct mg_connection *c, int ev, void *p);

	std::string sharedAddress;
};

#endif //APPSERVER_CONNECTIONTOSHARED_H
