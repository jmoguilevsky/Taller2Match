//
// Created by chris on 06/05/16.
//

#ifndef APPSERVER_CHAT_H
#define APPSERVER_CHAT_H

#include "../DB/ChatDB.h"

//! Handler para los requests relacionados con el login.

class Chat {

public:
	Chat(ChatDB &chatDB) : chatDB(chatDB) { }

private:
	ChatDB &chatDB;

};


#endif //APPSERVER_CHAT_H
