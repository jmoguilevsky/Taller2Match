#ifndef APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
#define APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H

#include "mongoose-master/mongoose.h"


// Un Mongoose Manager

class MgConnectionManager {

public:
	MgConnectionManager();

	~MgConnectionManager();

	mg_connection *configureListeningConnection(std::string port, void *data, mg_event_handler_t eventHandler);

	void poll(int everyMilliseconds);

	mg_connection *configureOutboundConnection(std::string url, void *data, mg_event_handler_t eventHandler);

private:
	mg_mgr mgr;
};


#endif //APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
