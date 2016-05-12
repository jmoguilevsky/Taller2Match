//
// Created by chris on 06/05/16.
//

#ifndef APPSERVER_CHAT_H
#define APPSERVER_CHAT_H

#include <iostream>
#include "../DB/ChatDB.h"
#include "../DB/ChatMessage.h"
#include "../DB/ChatHistory.h"

//! Handler para los requests relacionados con el login.

class Chat {

public:
	Chat(ChatDB &chatDB) : chatDB(chatDB) { }

	void sendMessage(ChatMessage &msg) {
		chatDB.save(msg.getUserFrom(), msg.getUserTo(), msg.toString());
	}

	std::string getChat(std::string userA, std::string userB) {
		std::string history = chatDB.getHistory(userA, userB);
		return history;
	}

	std::vector<ChatMessage> getUnread(std::string userA, std::string userB) {
		std::string history = chatDB.getHistory(userA, userB);
		ChatHistory chatHistory(history);
		std::vector<ChatMessage> unread = chatHistory.getUnread(userA);
		chatHistory.updateRead();
		std::string h = utils::JsonToString(chatHistory.getJson());
		chatDB.updateHistory(userA, userB, h);
		return unread;
	}


private:
	ChatDB &chatDB;

};


#endif //APPSERVER_CHAT_H
