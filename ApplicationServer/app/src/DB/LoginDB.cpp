//
// Created by chris on 24/04/16.
//
#include "LoginDB.h"

int LoginDB::newUser(std::string user, std::string pass) {
	std::cout << "before:" << std::endl;
	std::string value;
	bool exists = db.get(user, value);
	std::cout << "value: " << value << " exists: " <<
	(exists ? "USER_EXISTS" : "DOESNT_EXIST") << std::endl;
	if (db.get(user, value)) {
		std::cout << "key exists" << std::endl;
		return USER_ALREADY_EXISTS;
	}
	db.save(user, pass);
	std::cout << "after: " << std::endl;
	exists = db.get(user, value);
	std::cout << "value: " << value << " exists: " << exists << std::endl;
	return USER_CREATED_OK;
}

int LoginDB::login(std::string user, std::string pass) {
	std::string value;
	bool exists = db.get(user, value);
	if (!exists) {
		return USER_DOESNT_EXIST;
	} else if (pass != value) {
		return WRONG_PASSWORD;
	}
	return LOGIN_OK;
}