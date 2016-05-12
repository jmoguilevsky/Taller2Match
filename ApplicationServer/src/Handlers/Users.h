//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H

#include "../DB/UsersDB.h"
#include "../SharedData.h"

#define ALREADY_LOGGED_IN 3
#define USER_NOT_CONNECTED 4
#define LOGOUT_OK 5;

//! Handler para la cosas relacionadas con el login, alta y baja de usuarios, etc.
// también mantiene los tokens, y qué usuarios están o no conectados.
class Users {
	std::map<std::string, std::string> connected; // Si está conectado, tiene como valor el token. Si no está conectado, el usuario no está en esta tabla.
	UsersDB &db;
	SharedData &sharedData;

	void invalidateToken(std::string email);

	std::string newToken(std::string email);
public:
	Users(UsersDB &db, SharedData &sharedData) : db(db), sharedData(sharedData) { }

	int login(std::string email, std::string password, std::string &token);

	bool checkToken(std::string email, std::string token);

	void logout(std::string email);;

	bool isConnected(std::string email);


	int signUp(std::string email, std::string password, UserProfile userProfile);
};

#endif //APPSERVER_LOGIN_H
