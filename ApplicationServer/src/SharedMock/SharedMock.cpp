//
// Created by chris on 02/06/16.
//

#include "SharedMock.h"

vector<UserProfile> SharedMock::getUsersList() {
    vector<UserProfile> users;
    for ( std::map<std::string, UserProfile>::iterator iter  = (this -> users).begin(); iter != (this -> users).end(); ++iter) {
        users . push_back(iter -> second);
    }
    return users;
}

UserProfile SharedMock::getUserProfile(string sharedId) {
    return users[sharedId];
}

std::string SharedMock::newUser(UserProfile userProfile) {
    std::string sharedId;
    // Supongo que el mail con el que viene el perfil siempre es nuevo, no se repite.
    sharedId = std::to_string(users.size() + 1);
    users[sharedId] = userProfile;
    return sharedId;
}

void SharedMock::updateProfile(string sharedId, UserProfile profile) {

    users[sharedId] = profile;
}







