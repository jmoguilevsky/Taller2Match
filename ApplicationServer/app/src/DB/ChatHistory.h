//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_CHATHISTORY_H
#define APPSERVER_CHATHISTORY_H

#include <string>
#include <vector>
#include "ChatMessage.h"
#include "../json/json.h"

//! Tiene todo el historial de mensajes entre los users A y B, en formato Json:
//!

class ChatHistory {
	std::string userA;
	std::string userB;
	std::vector<ChatMessage> history;
public:
	ChatHistory(std::string userA, std::string userB, Json::Value &history);
};


#endif //APPSERVER_CHATHISTORY_H
