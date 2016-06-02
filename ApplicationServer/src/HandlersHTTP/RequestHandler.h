//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_HANDLERSELECTOR_H
#define APPSERVER_HANDLERSELECTOR_H

//! Request Handler genérico

#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"

class RequestHandler {

public:
	//! Recibe un request HTTP, y devuelve la respuesta al mismo.
	virtual HTTPResponse handle(HTTPRequest &request) = 0;
};


#endif //APPSERVER_HANDLERSELECTOR_H
