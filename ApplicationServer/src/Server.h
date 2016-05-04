#ifndef MULTITHREADMULTICONNECTION_SERVER_H
#define MULTITHREADMULTICONNECTION_SERVER_H

#include <iostream>
#include "mongoose-master/MongooseConnectionManager.h"
#include "mongoose-master/mongoose.h"
#include "HTTPRequest.h"
#include "HTTPRequestSender.h"
#include "Handlers/RequestHandler.h"
#include "HandlerSelector.h"
#include "SharedServerConnection.h"
#include <map>
#include <vector>

class Server {
private:
    MongooseConnectionManager mongooseConnectionManager;
    HandlerSelector handlerSelector;
    bool isServerUP;
	SharedServerConnection sharedServer;
    RequestHandler* getRequestHandler(HTTPRequest request);
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

