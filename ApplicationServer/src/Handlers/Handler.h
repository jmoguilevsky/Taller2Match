//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_REQUESTHANDLER_H
#define APPSERVER_REQUESTHANDLER_H

#include "../HTTPRequest.h"
#include "../HTTPResponse.h"

//! Handler genérico para un request de un usuario.
class Handler {
protected:
	HTTPRequest request;

public:
	Handler(HTTPRequest request) { this->request = request; }
	//! Los handlers específicos para cada request implementan el handle() correspondiente. Devuelve un HTTPResponse que se enviará al usuario que envió el request.
	virtual HTTPResponse handle() = 0;
};

#endif //APPSERVER_REQUESTHANDLER_H
