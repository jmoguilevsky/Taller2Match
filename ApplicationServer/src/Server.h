//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_SERVER_H
#define MULTITHREADMULTICONNECTION_SERVER_H

#include <iostream>
#include "mongoose-master/mongoose.h"
#include "HTTPRequest.h"
#include "HTTPRequestSender.h"
#include "Handlers/RequestHandler.h"
#include "DB/LoginDB.h"
#include "TokenManager.h"
#include "SharedServerConnection.h"
#include "DB/MatchesDB.h"
#include <map>
#include <vector>

//! Clase principal, el Server. (?)
class Server {
	struct mg_mgr mgr;
	struct mg_connection *listeningConnection;
	bool CONTINUE;
	LoginDB db;
	MatchesDB matchesDB;
	TokenManager tokenManager;
	RequestHandler *getRequestHandler(HTTPRequest request);

	SharedServerConnection sharedServer;
public:
	//! Inicia el server.
	void start();

	//! Detiene el server.
	void stop();

	//! Event handler para las conexiones con los clientes.
	// TODO: Explicar que es cada argumento al menos.
	static void clientHandler(mg_connection *c, int ev,
	                          void *p);

	//! Crea el server con un port donde escucha conexiones entrantes, y una URL (URL:port) del Shared Server.
	Server(std::string port, std::string sharedAddress);

	~Server();
};

#endif //MULTITHREADMULTICONNECTION_SERVER_H

