//
// Created by chris on 02/06/16.
//

#include <iostream>
#include "SharedMock.h"

vector<UserProfile> SharedMock::getUsersList() {
    vector<UserProfile> users;

    std::map<std::string, std::string> all = db -> listAll();

    for (std::map<std::string, std::string>::iterator iter = all . begin(); iter != all . end(); ++iter) {
        Json::Value js = util::stringToJson(iter -> second);
        users . push_back(UserProfile(js));
    }
    return users;
}

UserProfile SharedMock::getUserProfile(string sharedId) {
    //return users[sharedId];
    std::string profile;
    db -> get (sharedId, profile);
    std::cout << "User profile: " << profile << std::endl;
    Json::Value profileJson = util::stringToJson(profile);

    UserProfile prof (profileJson);

    return prof;
}

std::string SharedMock::newUser(UserProfile userProfile) {
    std::string sharedId;
    // Supongo que el mail con el que viene el perfil siempre es nuevo, no se repite.
    sharedId = std::to_string(n + 1);
    std::cout << "User profile: " << util::JsonToString(userProfile . getJson()) << std::endl;
    db -> save(sharedId, util::JsonToString(userProfile . getJson()));
    n++;

//    users[sharedId] = userProfile;
    return sharedId;

}

void SharedMock::updateProfile(string sharedId, UserProfile profile) {
    db -> save(sharedId, util::JsonToString(profile.getJson()));
    //users[sharedId] = profile;
}


std::vector<Interest> SharedMock::getAllInterests() {return std::vector<Interest>();}