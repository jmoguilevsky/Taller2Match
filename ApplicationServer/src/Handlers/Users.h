//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H

#include "../SharedData.h"
#include "../DB/KeyValueDB.h"
#include "../DB/RocksDB.h"
#include "../UsersProfiles.h"

#define ALREADY_LOGGED_IN 3
#define USER_NOT_CONNECTED 4
#define LOGOUT_OK 5;

//! Handler para la cosas relacionadas con el login, alta y baja de usuarios, etc.
// también mantiene los tokens, y qué usuarios están o no conectados.

class Users {

    std::map<std::string, std::string> token_userId_map;
    std::map<std::string, bool> userId_connected_map; // Si está conectado, tiene como valor el token. Si no está conectado, el usuario no está en esta tabla.
    UsersProfiles &userProfiles;
    RocksDB* email_pwd_db;
    RocksDB* email_sharedId_db;
    RocksDB* email_appId_db;
    RocksDB* appId_email_db;

    void invalidateToken(std::string token);

    std::string newToken(std::string appId);

public:

    Users(UsersProfiles &users);

    bool signUp(std::string email, std::string password, UserProfile userProfile);

    bool updateProfile(std::string userId, UserProfile newProfile);

    bool updatePhoto(std::string userId, Json::Value newPhoto);

    bool login(std::string email, std::string password, std::string* token, UserProfile* profile);

    void logout(std::string token);

    bool userExists(std::string userId) {
        return true;
    }

    bool isConnected(std::string email) ;

    bool getUserProfile(std::string userId, UserProfile* prof) ;

    bool getUserId(string token, string *userId);
};

#endif //APPSERVER_LOGIN_H
