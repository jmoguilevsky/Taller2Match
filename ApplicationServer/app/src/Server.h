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
#include "DB/LoginDB.h"
#include <map>
#include <vector>

//! Clase principal, el Server. (?)
class Server {
	struct mg_mgr mgr;
	struct mg_connection *listeningConnection;
	bool CONTINUE;
	std::string port;
	std::string sharedAddress;
	std::map<std::string, std::string> userPass;
	LoginDB db;

	RequestHandler *getRequestHandler(HTTPRequest request);
public:
	//! Inicia el server.
	void start();

	//! Detiene el server.
	void stop();

	//! Event handler para las conexiones con los clientes.
	static void clientHandler(mg_connection *c, int ev,
	                          void *p);

	//! Crea el server con un port donde escucha conexiones entrantes, y una URL (URL:port) del Shared Server.
	Server(std::string port, std::string sharedAddress);

	~Server();
};

#endif //MULTITHREADMULTICONNECTION_SERVER_H

