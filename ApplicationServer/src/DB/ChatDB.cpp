//
// Created by chris on 24/04/16.
//


#include <iostream>
#include "ChatDB.h"

std::string ChatDB::buildKey(std::string userA, std::string userB) {
	std::string key;
	if (userA < userB) key = userA + ":" + userB;
	else key = userB + ":" + userA;
	return key;
}

void ChatDB::save(std::string userA, std::string userB, std::string msg) {
	//TODO agregar el msg algo que diga si fue enviado a B o no.
	std::string key = buildKey(userA, userB);
	Json::Value mes = utils::stringToJson(msg);
	append(db, key, mes);
	std::cout << "History " << key << std::endl;
	std::string history;
	db.get(key, history);
	std::cout << history << std::endl;
}

std::string ChatDB::getHistory(std::string userA, std::string userB) {
	std::string key = buildKey(userA, userB);
	std::string history;
	db.get(key, history);
	return history;
}

void ChatDB::updateHistory(std::string userA, std::string userB, std::string history) {
	std::string key = buildKey(userA, userB);
	db.save(key, history);
}

ChatDB::ChatDB(KeyValueDB &db) : db(db) {

}