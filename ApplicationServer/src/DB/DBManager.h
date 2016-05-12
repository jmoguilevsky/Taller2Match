//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_MATCHDB_H
#define APPSERVER_MATCHDB_H


#include "UsersDB.h"
#include "MatchesDB.h"
#include "ChatDB.h"

//! Para agrupar todas las bases de datos usadas por la aplicación.

class DBManager {
	RocksDB* loginDB;
	RocksDB* likesDB;
	RocksDB* matchesDB;
	RocksDB* noMatchesDB;
	UsersDB *login;
	MatchesDB* matches;
public:
	DBManager(std::string loginDBname, std::string likesDBname, std::string matchesDBname, std::string noMatchesDBname);

	UsersDB &getLoginDB();

	MatchesDB & getMatchesDB();

	ChatDB &getChatDB();

	~DBManager();

	RocksDB *chatDB;
	ChatDB *chat;
};


#endif //APPSERVER_MATCHDB_H
