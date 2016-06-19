//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "RequestHandler.h"
#include "UsersHTTP.h"
#include "ChatHTTP.h"
#include "MatchHTTP.h"
#include "../MatchData/Chat.h"
//! Request handler para el app server.

class MatchRequestHandler : public RequestHandler {

	std::map<std::string, int> handlers;

	ProfilesDatabase* usersProfiles;
	ConnectedUsers connected;
	Chat* chat;
	Matcher* matcher;

	UsersHTTP *usersHttp;
	ChatHTTP *chatHttp;
	MatchHTTP *matcherHttp;

public:

	MatchRequestHandler(SharedProfilesDatabase &sharedData);

	HTTPResponse handle(HTTPRequest &request);

};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
