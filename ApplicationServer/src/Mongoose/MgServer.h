#ifndef MULTITHREADMULTICONNECTION_SERVER_H
#define MULTITHREADMULTICONNECTION_SERVER_H

#include <iostream>
#include "MgConnectionManager.h"
#include "mongoose-master/mongoose.h"
#include "../HTTP/HTTPRequest.h"
#include "MgHTTPClient.h"
#include "../HandlersHTTP/RequestHandler.h"
#include <map>
#include <vector>

//! Mongoose multithreaded server. La conexión se cierran después de enviar la respuesta al cliente.
class MgServer {
private:
	MgConnectionManager mongooseConnectionManager;
	RequestHandler &requestHandler;
    bool isServerUP;
	mg_connection* c;

	//! Event handler para las conexiones con los clientes.
	// TODO: Explicar que es cada argumento al menos.
	static void clientHandler(mg_connection *c, int ev,
	                          void *p);
public:
	//! Inicia el server.
	void start();

	//! Detiene el server.
	void stop();


	//! Crea el server con un port donde escucha conexiones entrantes, y una URL (URL:port) del Shared MgServer.
	MgServer(std::string port, RequestHandler &handlerSelector);

	~MgServer();

};

#endif //MULTITHREADMULTICONNECTION_SERVER_H

