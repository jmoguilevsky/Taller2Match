//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_CHATHTTP_H
#define APPSERVER_CHATHTTP_H


#include "../HTTP/HTTP.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "Chat.h"

//! Esta clase maneja los requests HTTP del chat.

class ChatHTTP {

	Chat *chat;

	HTTPResponse handleGetUnread(HTTPRequest request);

	HTTPResponse handleSendChat(HTTPRequest request);

public:
	ChatHTTP(ChatDB &db);

	HTTPResponse handle(HTTPRequest request);

	~ChatHTTP();
};


#endif //APPSERVER_CHATHTTP_H
