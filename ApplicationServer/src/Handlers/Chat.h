//
// Created by chris on 06/05/16.
//

#ifndef APPSERVER_CHAT_H
#define APPSERVER_CHAT_H

#include <iostream>
#include "../DB/RocksDb.h"
#include "../DB/JsonArrayDb.h"

//! Handler para las cosas relacionadas con el chat.

class Chat {
    JsonArrayDb *chat_db;
public:

    void sendMessage(std::string userId, std::string otherUserId, std::string content);

    std::string getHistory(std::string userA, std::string userB) const;

};




#endif //APPSERVER_CHAT_H
