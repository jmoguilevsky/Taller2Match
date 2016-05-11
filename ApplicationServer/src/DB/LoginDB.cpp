//
// Created by chris on 24/04/16.
//
#include "LoginDB.h"

bool LoginDB::newUser(std::string user, std::string pass) {
	std::string value;
	bool exists = db.get(user, value);
	if (db.get(user, value)) {
		return false;
	}
	db.save(user, pass);
	exists = db.get(user, value);
	return true;
}

int LoginDB::login(std::string user, std::string pass) {
	std::string value;
	bool exists = db.get(user, value);
	if (!exists || pass != value) {
		return LOGIN_ERROR;
	}
	return LOGIN_OK;
}

std::map<std::string, std::string> LoginDB::listAll() {
	return db.listAll();
};