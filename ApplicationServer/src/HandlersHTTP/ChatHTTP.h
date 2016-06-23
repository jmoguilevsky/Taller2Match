//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_CHATHTTP_H
#define APPSERVER_CHATHTTP_H


#include "../HTTP/HTTP.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "../MatchData/Chat.h"
#include "../MatchData/Matcher.h"
#include "../MatchData/ConnectedUsers.h"
//! Esta clase maneja los requests HTTP del chat.

class ChatHTTP {

    Matcher &matcher;

    ConnectedUsers& connected;

    Chat &chat;

    HTTPResponse handleSendChat(HTTPRequest request);

    HTTPResponse handleGetHistory(HTTPRequest request);

public:

    ChatHTTP(Matcher &matcher, Chat &chat, ConnectedUsers &connected)
            : matcher(matcher), chat(chat), connected(connected) { }

    HTTPResponse handle(HTTPRequest request);

    HTTPResponse handleGetNew(HTTPRequest request);
};


#endif //APPSERVER_CHATHTTP_H
