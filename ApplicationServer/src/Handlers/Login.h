//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H

#include "../DB/LoginDB.h"
#include "../SharedData.h"

//! Handler para los requests relacionados con el login.

#define ALREADY_LOGGED_IN 3
#define USER_NOT_CONNECTED 4
#define LOGOUT_OK 5;
class Login {
	std::map<std::string, std::string> connected; // Si está conectado, tiene como valor el token. Si no está conectado, el usuario no está en esta tabla.
	LoginDB &db;
	SharedData &sharedData;

	void invalidateToken(std::string email);

	std::string newToken(std::string email);
public:
	Login(LoginDB &db, SharedData &sharedData) : db(db), sharedData(sharedData) { }

	int login(std::string email, std::string password, std::string &token);

	bool checkToken(std::string email, std::string token);

	void logout(std::string email);;

	bool isConnected(std::string email);


};

#endif //APPSERVER_LOGIN_H
