//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H


#include "RequestHandler.h"
#include "../DB/LoginDB.h"
#include "../HTTPResponse.h"

class Login : public RequestHandler {
private:
	HTTPRequest request;
	LoginDB &db;
public:
	Login(HTTPRequest request, LoginDB &db);

	HTTPResponse handle();
};


#endif //APPSERVER_LOGIN_H
