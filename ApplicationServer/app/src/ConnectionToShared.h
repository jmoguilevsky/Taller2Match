//
// Created by chris on 23/04/16.
//

#ifndef APPSERVER_CONNECTIONTOSHARED_H
#define APPSERVER_CONNECTIONTOSHARED_H

#include "HTTPRequest.h"
#include "mongoose-master/mongoose.h"

//! Una conexión al Shared Server, para hacer un request y esperar por la respuesta.
class ConnectionToShared {

	struct mg_mgr mgr;
	struct mg_connection *c;
	HTTPRequest response;
	bool waiting;
	std::string sharedAddress;
public:
	//! Crea la conexión al Shared Server, recibiendo su URL como parámetro.
	ConnectionToShared(std::string sharedAddress);

	//! Envia un request HTTP al Shared Server, espera por la respuesta, y la devuelve como HTTPResponse.
	HTTPRequest sendRequest(HTTPRequest request);

	//! Handler para los eventos relacionados con la conexión al Shared Server.
	void handle(mg_connection *pConnection, int ev, void *p);

	//! Handler que deriva el evento hacia el ConnectionToShared particular de cada conexión.
	static void sharedHandler(struct mg_connection *c, int ev, void *p);
};

#endif //APPSERVER_CONNECTIONTOSHARED_H
