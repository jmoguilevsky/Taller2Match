//
// Created by chris on 23/04/16.
//

#ifndef APPSERVER_CONNECTIONTOSHARED_H
#define APPSERVER_CONNECTIONTOSHARED_H

#include "../HTTP/HTTPRequest.h"
#include "mongoose-master/mongoose.h"
#include "../HTTP/HTTPResponse.h"
#include "MgConnectionManager.h"

//! Una conexión a un server HTTP, la conexión se cierra inmediatamnte después de obtener la respuesta al request.

class MgHTTPClient {

private:

	mg_connection *c;
	MgConnectionManager mgr;
	HTTPResponse response;
	bool waiting;

	//! Handler para los eventos relacionados con la conexión al Shared MgServer.
	void handle(mg_connection *c, int ev, void *p);

	//! Handler que deriva el evento hacia el MgHTTPClient particular de cada conexión.
	static void eventHandler(mg_connection *c, int ev, void *p);

public:
	MgHTTPClient() {
		c = NULL;
	}

	//! Crea la conexión al Shared MgServer, recibiendo su URL como parámetro.
	bool connectToUrl(std::string url);

	//! Envia un request HTTP al Shared MgServer, espera por la respuesta, y la devuelve como HTTPResponse.
	HTTPResponse sendRequest(HTTPRequest request);
};

#endif //APPSERVER_CONNECTIONTOSHARED_H
