//
// Created by chris on 06/05/16.
//

#ifndef APPSERVER_CHAT_H
#define APPSERVER_CHAT_H


#include "Handler.h"
#include "../DB/LoginDB.h"
#include "../HTTP/HTTPResponse.h"
#include "../TokenManager.h"
#include "../DB/DBManager.h"
#include "../DB/ChatDB.h"

//! Handler para los requests relacionados con el login.

class Chat : public Handler {

private:

	MatchesDB &matchesDB;
	ChatDB &chatDB;

public:

	Chat(HTTPRequest request, ChatDB &chatDB, MatchesDB &matchesDb);

	HTTPResponse handle();
};


#endif //APPSERVER_CHAT_H
