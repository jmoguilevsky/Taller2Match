//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H


#include "Handler.h"
#include "../DB/LoginDB.h"
#include "../HTTPResponse.h"
#include "../TokenManager.h"
#include "../SharedServerConnection.h"
#include "../DB/DBManager.h"

//! Handler para los requests relacionados con el login.

class Login : public Handler {

private:

	TokenManager &tokenManager;
	LoginDB &db;
	SharedData &sharedData;

public:

	Login(HTTPRequest request, LoginDB &db, TokenManager &tokenManager,
	      SharedData &sharedData);

	HTTPResponse handle();
};

#endif //APPSERVER_LOGIN_H
