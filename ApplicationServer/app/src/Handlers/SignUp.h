//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_SIGNUP_H
#define APPSERVER_SIGNUP_H


#include "RequestHandler.h"
#include "../DB/LoginDB.h"

//! Handler para la creación de un nuevo usuario.
class SignUp : public RequestHandler {
private:
	LoginDB &db;
public:
	SignUp(HTTPRequest request, LoginDB &db);

	HTTPResponse handle();
};


#endif //APPSERVER_SIGNUP_H
