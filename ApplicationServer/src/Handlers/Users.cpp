//
// Created by chris on 24/04/16.
//

#include <fstream>
#include <iostream>
#include "Users.h"


bool Users::signUp(std::string email, std::string password, UserProfile userProfile) {

    std::string value;

    bool exists = email_pwd_db->get(email, value);

    if(exists) return false; // El usuario ya existe en el app server

    std::string userId;

    bool ok = userProfiles.newUser(userProfile, &userId);

    if(!ok) return false; // No se pudo crear en el shared server

    email_pwd_db -> save(email, password);

    return true;
}

bool Users::login(std::string email, std::string password, std::string* token, UserProfile* profile) {

    std::string value;

    std::cout << "EMAIL - PASSWORD" << std::endl;

    email_pwd_db->listAll();

    bool exists = email_pwd_db->get(email, value);

    if(!exists) return false; // El usuario no está registrado acá

    if(password != value) return false; // La contraseña no es correcta

    string userId;

    userId = userProfiles.getUserId(email);

    if(isConnected(userId)) return false; // El usuario ya está conectado

    UserProfile auxProfile;

    bool existsInShared = userProfiles.getProfile(userId,&auxProfile);

    if(!existsInShared) return false; // El usuario no está en el shared

    *token = newToken(userId);

    *profile = auxProfile;

    return true;
}

bool Users::isConnected(std::string userId) {
    return userId_connected_map[userId];
}

bool Users::getUserId(std::string token, std::string* userId){
    if(token_userId_map.count(token) == 0) return false;
    *userId = token_userId_map[token];
    return true;
}

void Users::invalidateToken(std::string token) {
    std::string userId = token_userId_map[token];
    userId_connected_map[userId] = false;
    token_userId_map.erase(token);
}

std::string Users::newToken(std::string userId) {
    std::string token = userId;
    token_userId_map[token] = userId;
    userId_connected_map[userId] = true;
    return token;
}

void Users::logout(std::string token) {
    invalidateToken(token);
}

bool Users::getUserProfile(std::string userId, UserProfile* profile) {
    // TODO A partir de este Id, buscar el Id en el shared, pedir el perfil y devolverlo.
    UserProfile aux;
    bool ok = userProfiles.getProfile(userId, &aux);
    if(!ok) return false;
    *profile = aux;
    return true;
}

bool Users::updatePhoto(std::string userId, Json::Value newPhoto) {
    return false;
}

bool Users::updateProfile(std::string userId, UserProfile newProfile) {
    return false;
}


Users::Users(UsersProfiles &users) : userProfiles(users) {
    email_pwd_db = new RocksDB("email_pwd");
    new RocksDB("email_sharedId");
    new RocksDB("email_appId");
    appId_email_db = new RocksDB("appId_email");
}