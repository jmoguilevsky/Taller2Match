//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_AUTHENTICATIONERROR_H
#define APPSERVER_AUTHENTICATIONERROR_H


#include "../HTTPResponse.h"
#include "Handler.h"

//! Este es el "handler" para cuando hay un error de autenticación, o sea, cuando la combinación
//! username, token no es válida (NO tiene nada que ver con lo que pasa durante el login, esto es
// después del login).
class AuthenticationError : public Handler {
public:
	AuthenticationError(const HTTPRequest &request);

	HTTPResponse handle();
};


#endif //APPSERVER_AUTHENTICATIONERROR_H
