//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_SERVER_H
#define MULTITHREADMULTICONNECTION_SERVER_H

#include <iostream>
#include "ClientHandler.h"
#include "../mongoose-master/mongoose.h"

class Server {

	static struct mg_mgr mgr;
	static struct mg_connection *listeningConnection;
	static std::vector<ClientHandler*> cHandlers;
	static bool CONTINUE;
	static std::string sharedAddress;
private:
	Server();
public:

	static void init(const std::string &port, const std::string &sharedAddress);

	static void stop();

	static void clientHandler(mg_connection *connectionToClient, int ev,
	                          void *p);
};

#endif //MULTITHREADMULTICONNECTION_SERVER_H

