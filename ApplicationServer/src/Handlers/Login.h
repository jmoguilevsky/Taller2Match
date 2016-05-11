//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H

#include "../DB/LoginDB.h"
#include "../TokenManager.h"
#include "../SharedData.h"

//! Handler para los requests relacionados con el login.

class Login {

	TokenManager tokenManager;
	LoginDB &db;
	SharedData &sharedData;

public:
	Login(LoginDB &db, SharedData &sharedData) : db(db), sharedData(sharedData) { }

	int login(std::string email, std::string password, std::string &token);
};

#endif //APPSERVER_LOGIN_H
