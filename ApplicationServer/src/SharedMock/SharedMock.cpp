//
// Created by chris on 02/06/16.
//

#include "SharedMock.h"

bool SharedMock::getUsersList(vector<UserProfile> *users) {
    for ( std::map<std::string, UserProfile>::iterator iter  = (this -> users).begin(); iter != (this -> users).end(); ++iter) {
        users -> push_back(iter -> second);
    }
    return true;
}

bool SharedMock::getUserProfile(string sharedId, UserProfile *userProfile) {
    if (users.count(sharedId) == 0) return false;
    *userProfile = users[sharedId];
    return true;
}

bool SharedMock::newUser(UserProfile userProfile, string *sharedId) {
    // Supongo que el mail con el que viene el perfil siempre es nuevo, no se repite.
    *sharedId = std::to_string(users.size() + 1);
    users[*sharedId] = userProfile;
    return true;
}

bool SharedMock::updateProfile(string sharedId, UserProfile profile) {
    if(users.count(sharedId) == 0) return false;
    users[sharedId] = profile;
    return true;
}







