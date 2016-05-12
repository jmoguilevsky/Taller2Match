//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_CHATDB_H
#define APPSERVER_CHATDB_H

#include "../utils.h"
#include "NoSQLDatabase.h"

//! Base de datos para historial de chats.
class ChatDB {
	NoSQLDatabase &db;
public:
	ChatDB(NoSQLDatabase &db);

	void save(std::string userA, std::string userB, std::string msg);

	std::string buildKey(std::string userA, std::string userB);

	std::string getHistory(std::string userA, std::string userB);

	void updateHistory(std::string userA, std::string userB, std::string history);
};


#endif //APPSERVER_CHATDB_H
