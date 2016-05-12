//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_USERSHTTP_H
#define APPSERVER_USERSHTTP_H


#include "Users.h"
#include "../HTTP/HTTPRequest.h"
#include "../HTTP/HTTPResponse.h"

//! Esta clase maneja los requests HTTP que tienen que ver con login, logout, etc...

class UsersHTTP {

	Users *users;

	HTTPResponse handleSignUp(HTTPRequest request);

	HTTPResponse handleLogin(HTTPRequest request);

	HTTPResponse handleLogout(HTTPRequest request);

public:

	UsersHTTP(UsersDB &usersDB, SharedData &sharedData);

	~UsersHTTP();

	HTTPResponse handle(HTTPRequest request);

	bool verifyCredentials(HTTPRequest request);
};


#endif //APPSERVER_USERSHTTP_H
