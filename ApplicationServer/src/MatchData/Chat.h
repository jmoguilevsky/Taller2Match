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

    Chat() {
        chat_db = new JsonArrayDb("db/chat_db");
    }

    //! "Envia" el mensaje enviado por el primer usuario al segundo. Guarda el mensaje en la base de datos.
    std::string sendMessage(std::string userId, std::string otherUserId, std::string content);

    //! Devuelve el historial de conversaciones completo entre los dos usuarios.
    std::string getHistory(std::string userA, std::string userB) const;

};




#endif //APPSERVER_CHAT_H
