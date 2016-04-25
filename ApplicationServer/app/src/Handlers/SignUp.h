//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_SIGNUP_H
#define APPSERVER_SIGNUP_H


#include "RequestHandler.h"
#include "../DB/LoginDB.h"

class SignUp : public RequestHandler {
private:
	HTTPRequest request;
	LoginDB &db;
public:
	SignUp(HTTPRequest request, LoginDB &db);

	HTTPResponse handle();
};


#endif //APPSERVER_SIGNUP_H
