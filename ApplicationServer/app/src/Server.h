//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_SERVER_H
#define MULTITHREADMULTICONNECTION_SERVER_H

#include <iostream>
#include "mongoose-master/mongoose.h"
#include "HTTPRequest.h"
#include "ConnectionToShared.h"
#include "Handlers/RequestHandler.h"
#include "DB/DBManager.h"
#include "DB/LoginDB.h"
#include <map>
#include <vector>

class Server {
	DBManager dbManager;
	struct mg_mgr mgr;
	struct mg_connection *listeningConnection;
	bool CONTINUE;
	std::string port;
	std::string sharedAddress;
	std::map<std::string, std::string> userPass;
	LoginDB db;
public:

	void start();

	void stop();

	static void clientHandler(mg_connection *c, int ev,
	                          void *p);

	Server(std::string port, std::string sharedAddress);

	~Server();

	RequestHandler *getRequestHandler(HTTPRequest request);
};

#endif //MULTITHREADMULTICONNECTION_SERVER_H

