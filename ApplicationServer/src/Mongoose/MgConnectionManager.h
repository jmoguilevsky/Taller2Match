#ifndef APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
#define APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H

#include "mongoose-master/mongoose.h"


//! Wrapper para un Mongoose Manager.

class MgConnectionManager {

public:
	MgConnectionManager();

	~MgConnectionManager();

	//! Devuelve una nueva mg_connection que escucha conexiones entrantes.

	mg_connection *configureListeningConnection(std::string port, void *data, mg_event_handler_t eventHandler);

	//! Wrapper para la función mg_poll de la librería mongoose.
	void poll(int everyMilliseconds);

	//! Devuelve una nueva mg_connection saliente hacia una url.
	mg_connection *configureOutboundConnection(std::string url, void *data, mg_event_handler_t eventHandler);

private:
	mg_mgr mgr;
};


#endif //APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
