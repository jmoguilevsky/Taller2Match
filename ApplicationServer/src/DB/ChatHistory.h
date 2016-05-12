//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_CHATHISTORY_H
#define APPSERVER_CHATHISTORY_H

#include <string>
#include <vector>
#include "ChatMessage.h"
#include "../json/json.h"
#include "../utils.h"

//! Tiene todo el historial de mensajes entre los users A y B, en formato Json:
//!

class ChatHistory {
	std::string userA;
	std::string userB;
	std::vector<ChatMessage> messages;
public:
	ChatHistory(std::string historyStr) {
		Json::Value history = utils::stringToJson(historyStr);
		for (int i = 0; i < history.size(); i++) {
			ChatMessage msg;
			msg.fromJson(history[i]);
			messages.push_back(msg);
		}
	}

	std::vector<ChatMessage> getUnread(std::string user) {
		return messages;
	}
};


#endif //APPSERVER_CHATHISTORY_H
