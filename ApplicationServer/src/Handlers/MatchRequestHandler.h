//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "../DB/LoginDB.h"
#include "../DB/MatchesDB.h"

#include "../SharedData.h"
#include "RequestHandler.h"
#include "../DB/DBManager.h"
#include "SignUp.h"
#include "Login.h"
#include "Chat.h"
#include "Matcher.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"

class MatchRequestHandler : public RequestHandler {
// TODO: Mandar cosas a private !
	std::map<std::string, bool> connected;
	std::map<std::string, std::map<std::string, int>> handlers;

	SignUp signUp;
	Login login;
	Chat chat;
	Matcher matcher;


	HTTPResponse handleSignUp(HTTPRequest request);

	HTTPResponse handleGetCandidates(HTTPRequest request);

	HTTPResponse handleSendChat(HTTPRequest request);

	HTTPResponse handleGetUnread(HTTPRequest request);

	HTTPResponse handleLike(HTTPRequest request);

	HTTPResponse handleLogin(HTTPRequest request);

	HTTPResponse handleNoMatch(HTTPRequest &request);

	HTTPResponse handleLogout(HTTPRequest &request);

public:

	MatchRequestHandler(DBManager &dbManager, SharedData &sharedData);

	~MatchRequestHandler();

	HTTPResponse handle(HTTPRequest &request);

	bool checkCredentials(HTTPRequest request);
};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
