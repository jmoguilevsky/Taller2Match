//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_CHATHTTP_H
#define APPSERVER_CHATHTTP_H


#include "../HTTP/HTTP.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "../Handlers/Chat.h"
#include "../Handlers/Users.h"
#include "../Handlers/Matcher.h"
//! Esta clase maneja los requests HTTP del chat.

class ChatHTTP {

    Users &users;

    Matcher &matcher;

    Chat &chat;

    HTTPResponse handleSendChat(HTTPRequest request);

    HTTPResponse handleGetHistory(HTTPRequest request);

public:

    ChatHTTP(Users &users,Matcher &matcher, Chat &chat) : users(users), matcher(matcher), chat(chat) { }

    HTTPResponse handle(HTTPRequest request);

};


#endif //APPSERVER_CHATHTTP_H
