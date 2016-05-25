//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "../SharedData.h"
#include "RequestHandler.h"
#include "UsersHTTP.h"
#include "ChatHTTP.h"
#include "MatcherHTTP.h"
#include "../UsersProfiles.h"
//! Request handler para el app server.

class MatchRequestHandler : public RequestHandler {

	std::map<std::string, int> handlers;
	UsersProfiles usersProfiles;
	Users* users;
	Chat* chat;
	Matcher* matches;

	UsersHTTP *usersHttp;
	ChatHTTP *chatHttp;
	MatcherHTTP *matcherHttp;

public:

	MatchRequestHandler(SharedData &sharedData);

	HTTPResponse handle(HTTPRequest &request);
};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
