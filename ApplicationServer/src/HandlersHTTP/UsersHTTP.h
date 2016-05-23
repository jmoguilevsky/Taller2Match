//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_USERSHTTP_H
#define APPSERVER_USERSHTTP_H


#include "../Handlers/Users.h"
#include "../HTTP/HTTPRequest.h"
#include "../HTTP/HTTPResponse.h"
#include "../Handlers/Matcher.h"

//! Esta clase maneja los requests HTTP que tienen que ver con login, logout, etc...

class UsersHTTP {

	Users& users;

	const Matcher& matcher;

	HTTPResponse handleSignUp(HTTPRequest request);

	HTTPResponse handleLogin(HTTPRequest request);

	HTTPResponse handleLogout(HTTPRequest request);

	HTTPResponse handleUpdateProfile(HTTPRequest request);

	HTTPResponse handleUpdatePhoto(HTTPRequest request);

	HTTPResponse handleViewProfile(HTTPRequest request);

public:

	UsersHTTP(Users& users, const Matcher& matcher): users(users), matcher(matcher){};

	HTTPResponse handle(HTTPRequest request);

};


#endif //APPSERVER_USERSHTTP_H
