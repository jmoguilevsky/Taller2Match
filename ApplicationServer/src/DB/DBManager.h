//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_MATCHDB_H
#define APPSERVER_MATCHDB_H


#include "LoginDB.h"
#include "MatchesDB.h"
#include "ChatDB.h"

class DBManager {
	RocksDB* loginDB;
	RocksDB* likesDB;
	RocksDB* matchesDB;
	RocksDB* noMatchesDB;
	LoginDB* login;
	MatchesDB* matches;
public:
	DBManager(std::string loginDBname, std::string likesDBname, std::string matchesDBname, std::string noMatchesDBname);

	LoginDB & getLoginDB();

	MatchesDB & getMatchesDB();

	ChatDB &getChatDB();

	~DBManager();
};


#endif //APPSERVER_MATCHDB_H
