//
// Created by chris on 24/04/16.
//


#include "ChatDB.h"

std::string ChatDB::buildKey(std::string userA, std::string userB) {
	std::string key;
	if (userA < userB) key = userA + userB;
	else key = userB + userA;
	return key;
}

void ChatDB::save(std::string userA, std::string userB, std::string msg) {
	//TODO agregar el msg algo que diga si fue enviado a B o no.
	std::string key = buildKey(userA, userB);
	db.save(key, msg);
}

std::string ChatDB::getUnreadMsgs(std::string userA, std::string userB) {
	std::string key = buildKey(userA, userB);
	std::string msgs;
	db.get(key, msgs);
	///
	return "";
}

ChatDB::ChatDB(NoSQLDatabase &db) : db(db) {

}