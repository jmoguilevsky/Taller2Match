//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "../DB/UsersDB.h"
#include "../DB/MatchesDB.h"
#include "../SharedData.h"
#include "RequestHandler.h"
#include "../DB/DBManager.h"
#include "Users.h"
#include "Chat.h"
#include "Matcher.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "UsersHTTP.h"
#include "ChatHTTP.h"
#include "MatcherHTTP.h"

//! Request handler para el app server.

class MatchRequestHandler : public RequestHandler {
// TODO: Mandar cosas a private !
	std::map<std::string, int> handlers;

	UsersHTTP *users;
	ChatHTTP *chat;
	MatcherHTTP *matcher;

public:

	MatchRequestHandler(DBManager &dbManager, SharedData &sharedData);

	HTTPResponse handle(HTTPRequest &request);
};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
