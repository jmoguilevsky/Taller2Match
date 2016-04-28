//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H


#include "RequestHandler.h"
#include "../DB/LoginDB.h"
#include "../HTTPResponse.h"
#include "../TokenManager.h"
#include "../SharedServerConnection.h"

//! Handler para los requests relacionados con el login.
class Login : public RequestHandler {
private:
	TokenManager &tokenManager;
	LoginDB &db;
public:
	Login(HTTPRequest request, LoginDB &db, TokenManager &tokenManager,
	      SharedServerConnection &sharedServer);

	HTTPResponse handle();

	SharedServerConnection &sharedServer;
};


#endif //APPSERVER_LOGIN_H
