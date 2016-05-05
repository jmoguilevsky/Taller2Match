//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_SIGNUP_H
#define APPSERVER_SIGNUP_H


#include "Handler.h"
#include "../DB/LoginDB.h"

//! Handler para la creación de un nuevo usuario.
class SignUp : public Handler {
private:
	LoginDB &db;
public:
	SignUp(HTTPRequest request, LoginDB &db);

	HTTPResponse handle();
};


#endif //APPSERVER_SIGNUP_H
