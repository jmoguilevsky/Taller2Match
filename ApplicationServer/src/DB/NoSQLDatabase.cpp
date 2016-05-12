//
// Created by chris on 11/05/16.
//

#include "NoSQLDatabase.h"

bool valueExists(NoSQLDatabase &db, std::string key, std::string value) {
	std::string values;
	db.get(key, values);
	Json::Value list = utils::stringToJson(values);
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == value) { return true; }
	}
	return false;
}

void append(NoSQLDatabase &db, std::string key, Json::Value value) {
	std::string oldList;
	db.get(key, oldList);

	Json::Value oldListJson = utils::stringToJson(oldList);

	//Json::Value newValueJson = value;

	oldListJson.append(value);

	db.save(key, utils::JsonToString(oldListJson));
}