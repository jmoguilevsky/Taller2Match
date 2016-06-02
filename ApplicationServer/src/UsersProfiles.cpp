//
// Created by chris on 23/05/16.
//

#include <iostream>
#include "UsersProfiles.h"

UsersProfiles::UsersProfiles() {
    userId_email_map = new RocksDb("userId_email");
    email_userId_map = new RocksDb("email_userId");
    email_sharedId_map = new RocksDb("email_sharedId");
    n = 0;
}

void UsersProfiles::setShared(SharedData &sharedData) {
    this->sharedData = &sharedData;
}

string UsersProfiles::getUserId(string email) {
    std::string userId;
    email_userId_map->get(email, userId);
    return userId;
}

bool UsersProfiles::getProfile(string userId, UserProfile *userProfile) {
    std::string email;
    userId_email_map->get(userId, email); // Si no existe ese userId en el app server -> ERROR
    if (email == "") return false;
    string sharedId;
    email_sharedId_map->get(email, sharedId);
    if (sharedId == "") return false;
    UserProfile aux;
    bool profileOk = sharedData->getUserProfile(sharedId, &aux);
    if (!profileOk) return false; // Si no existe ese sharedId en el shared server, o hubo otro error -> ERROR
    *userProfile = aux;
    userProfile->changeId(userId);
    return true; // OK
}

bool UsersProfiles::newUser(UserProfile userProfile, string *userId) {
    string email = userProfile.getEmail();

    std::cout << "EMAIL - USERID" << std::endl;
    email_userId_map->listAll();

    std::cout << "USERID - EMAIL" << std::endl;
    userId_email_map->listAll();

    string sharedId;
    email_sharedId_map->get(email, sharedId);
    if (sharedId != "") return false;
    bool newUserOk = sharedData->newUser(userProfile, &sharedId);
    if (!newUserOk) return false; // Si no se pudo crear en el shared -> ERROR
    *userId = getNextId();
    email_sharedId_map->save(email, sharedId); // Registrar sharedId para ese email
    userId_email_map->save(*userId, email); // Registrar email para el userId
    email_userId_map->save(email, *userId);

    return true;
}

bool UsersProfiles::getUsers(map<string, UserProfile> *users) {
    vector<UserProfile> aux;
    bool usersOk = sharedData->getUsersList(&aux); // Pido todos los usuarios del shared
    if (!usersOk) return false; // Su hubo algún error en el shared -> ERROR
    for (int i = 0; i < aux.size(); i++) {
        std::string userId;
        email_userId_map->get(aux[i].getEmail(), userId);
        if (userId != "") {
            aux[i].changeId(userId); // Cambiar el sharedId por el userId del app server
            (*users)[userId] = aux[i]; //Agregar a la lista de los usuarios
        }
    }
    return true;
}

string UsersProfiles::getNextId() {
    if (n == 0) n = atoi((userId_email_map->getLastKey()).c_str());
    n++;
    return std::to_string(n);
}

bool UsersProfiles::updateProfile(string userId, UserProfile userProfile) {
    std::string email;
    userId_email_map->get(userId, email);
    std::string sharedId;
    email_sharedId_map->get(email, sharedId);
    userProfile.changeId(sharedId);
    bool ok = sharedData->updateProfile(sharedId, userProfile);
    return ok;
}

