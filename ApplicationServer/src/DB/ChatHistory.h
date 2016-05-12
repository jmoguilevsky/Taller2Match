//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_CHATHISTORY_H
#define APPSERVER_CHATHISTORY_H

#include <string>
#include <vector>
#include <iostream>
#include "ChatMessage.h"
#include "../json/json.h"
#include "../utils.h"

//! Tiene todo el historial de mensajes entre los users A y B, en formato Json:
//!

class ChatHistory {
	std::string userA;
	std::string userB;
	std::vector<ChatMessage> messages;
	Json::Value history;
public:
	ChatHistory(std::string historyStr) {
		history = utils::stringToJson(historyStr);
		for (int i = 0; i < history.size(); i++) {
			ChatMessage msg;
			msg.fromJson(history["messages"][i]);
			messages.push_back(msg);
		}
	}

	std::vector<ChatMessage> getUnread(std::string user) {
		std::vector<ChatMessage> unread;
		for (int i = 0; i < messages.size(); i++) {
			if (!messages[i].isRead() && messages[i].getUserTo() == user) {
				ChatMessage m = messages[i];
				m.setRead();
				messages[i] = m;
				std::cout << m.toString() << std::endl;
				unread.push_back(messages[i]);
			}
		}
		return unread;
	}

	void updateRead() {
		// Guardo el historial modificado con los mensajes ya leídos
		Json::Value array;

		for (int i = 0; i < messages.size(); i++) {
			array.append(messages[i].toJson());
		}
		Json::Value empty;
		history = empty;
		history["messages"] = array;
	}

	Json::Value getJson() {
		return history;
	}
};


#endif //APPSERVER_CHATHISTORY_H
