//
// Created by chris on 23/05/16.
//

#include <iostream>
#include "ProfilesDatabase.h"
#include "../Exceptions/Exception.h"

ProfilesDatabase::ProfilesDatabase() {
    userId_email_map = new RocksDb("db/userId_email");
    email_userId_map = new RocksDb("db/email_userId");
    email_sharedId_map = new RocksDb("db/email_sharedId");
    email_pwd_map = new RocksDb("db/email_pwd");
    n = 0;
}

void ProfilesDatabase::setShared(SharedProfilesDatabase &sharedData) {
    this -> sharedData = &sharedData;
}

string ProfilesDatabase::getUserId(string email) {
    if(!email_userId_map->hasKey(email)) throw Exception("User not registered in server");
    std::string userId;
    email_userId_map -> get(email, userId);
    return userId;
}

UserProfile ProfilesDatabase::getProfile(string userId) {
    std::string email;
    userId_email_map -> get(userId, email);
    if (email == "") throw Exception("User not registered in server");
    string sharedId;
    std::cout << "LISTING ALL USERS EMAIL - SHARED" << std::endl;
    email_sharedId_map -> listAll();
    email_sharedId_map -> get(email, sharedId);

    if (sharedId == "") throw Exception("User not registered in server");
    UserProfile profile = sharedData -> getUserProfile(sharedId);
    profile . changeId(userId);
    return profile;
}

void ProfilesDatabase::newUser(std::string email, std::string password, UserProfile userProfile) {
    if(email_sharedId_map->hasKey(email)) throw Exception("Email already registered in server");
    std::cout<<"asdasd";
    std::string sharedId = sharedData -> newUser(userProfile);
    std::cout << "User created with shared Id: " << sharedId << std::endl;
    std::cout<<"asdasd2";
    std::string userId = getNextId();
    email_sharedId_map -> save(email, sharedId); // Registrar sharedId para ese email
    userId_email_map -> save(userId, email); // Registrar email para el userId
    email_userId_map -> save(email, userId);
    email_pwd_map -> save(email, password);
}

map<string, UserProfile> ProfilesDatabase::getUsers() {
    vector<UserProfile> users = sharedData -> getUsersList(); // Pido todos los usuarios del shared
    map<string, UserProfile> usersMap;
    for (int i = 0; i < users . size(); i++) {
        std::string userId;
        email_userId_map -> get(users[i] . getEmail(), userId);
        if (userId != "") {
            users[i] . changeId(userId); // Cambiar el sharedId por el userId del app server
            usersMap[userId] = users[i]; //Agregar a la lista de los usuarios
        }
    }
    return usersMap;
}

string ProfilesDatabase::getNextId() {
    if (n == 0) n = atoi((userId_email_map -> getLastKey()) . c_str());
    n++;
    return std::to_string(n);
}

void ProfilesDatabase::updateProfile(string userId, UserProfile userProfile) {
    std::string email;
    userId_email_map -> get(userId, email);
    std::string sharedId;
    email_sharedId_map -> get(email, sharedId);
    userProfile . changeId(sharedId);
    sharedData -> updateProfile(sharedId, userProfile);
}

std::vector<Interest> ProfilesDatabase::getAllInterests(){
    return sharedData -> getAllInterests();
}

bool ProfilesDatabase::verify(string email, string password) {
    std::string pass;
    if(!email_pwd_map->hasKey(email)) throw Exception("User not registered in server");
    email_pwd_map -> get(email, pass);
    return password == pass;
}

