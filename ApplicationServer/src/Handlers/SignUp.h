//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_SIGNUP_H
#define APPSERVER_SIGNUP_H


#include "../DB/LoginDB.h"
#include "../UserProfile.h"
#include "../SharedData.h"

#define USER_CREATED 201

//#define USER_ALREADY_EXISTS 400
//! Handler para la creación de un nuevo usuario.
class SignUp {
private:
	LoginDB &db;
	SharedData &sharedData;
public:
	SignUp(LoginDB &db, SharedData &sharedData) : db(db), sharedData(sharedData) { }

	int signUp(std::string email, std::string password, UserProfile userProfile);
};


#endif //APPSERVER_SIGNUP_H
