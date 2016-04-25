//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGINDB_H
#define APPSERVER_LOGINDB_H


#include <iostream>
#include "DB.h"

#define USER_ALREADY_EXISTS 1
#define USER_CREATED_OK 0

#define USER_DOESNT_EXIST 2
#define WRONG_PASSWORD 1
#define LOGIN_OK 0

class LoginDB {
	DB db;
public:
	LoginDB(std::string name) : db(name) {
	}

	int newUser(std::string user, std::string pass) {
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

	int login(std::string user, std::string pass) {
		std::string value;
		bool exists = db.get(user, value);
		if (!exists) {
			return USER_DOESNT_EXIST;
		} else if (pass != value) {
			return WRONG_PASSWORD;
		}
		return LOGIN_OK;
	}
};

#endif //APPSERVER_LOGINDB_H
