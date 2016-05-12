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
		std::cout << "MSG TO STRING: " << msg.toString() << std::endl;
		chatDB.save(msg.getUserFrom(), msg.getUserTo(), msg.toString());
	}

	std::string getChat(std::string userA, std::string userB) {
		std::string history = chatDB.getHistory(userA, userB);
		return history;
	}


private:
	ChatDB &chatDB;

};


#endif //APPSERVER_CHAT_H
