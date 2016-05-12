//
// Created by chris on 04/05/16.
//

#include "DBManager.h"

DBManager::DBManager(std::string loginDBname, std::string likesDBname, std::string matchesDBname, std::string noMatchesDBname) {
	loginDB = new RocksDB(loginDBname);
	likesDB = new RocksDB(likesDBname);
	matchesDB = new RocksDB(matchesDBname);
	noMatchesDB = new RocksDB(noMatchesDBname);
	chatDB = new RocksDB("chat");
	login = new LoginDB(*loginDB);
	matches = new MatchesDB(*noMatchesDB,*likesDB,*matchesDB);
	chat = new ChatDB(*chatDB);
}

LoginDB &DBManager::getLoginDB() {
	return *login;
}

MatchesDB &DBManager::getMatchesDB() {
	return *matches;
}

DBManager::~DBManager() {
	delete loginDB;
	delete likesDB;
	delete matchesDB;
	delete noMatchesDB;
	delete chatDB;
	delete chat;
	delete login;
	delete matches;
}

ChatDB &DBManager::getChatDB() {
	return *chat;
}

