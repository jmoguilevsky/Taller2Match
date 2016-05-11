//
// Created by chris on 08/05/16.
//

#include "MatchesDB.h"
#include <iostream>
#include "JsonList.h"

JsonList::JsonList(std::__cxx11::string jsonList) {
	Json::Value array = utils::stringToJson(jsonList);
	for (Json::ValueConstIterator iter = array.begin(); iter != array.end(); ++iter) {
		users.push_back((*iter).asString());
	}
}

void JsonList::append(std::__cxx11::string str) {
	users.push_back(str);
}

bool JsonList::hasValue(std::__cxx11::string str) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i] == str)return false;
	}
	return true;
}

std::__cxx11::string JsonList::asString() {
	Json::Value array;
	for (int i = 0; i < users.size(); i++) {
		Json::Value user = utils::stringToJson(users[i]);
		array.append(user);
	}
	return array.asString();
}