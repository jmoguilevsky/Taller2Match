//
// Created by chris on 26/03/16.
//

#include "UserProfile.h"
#include "util.h"
#include <iostream>

UserProfile::UserProfile(Json::Value &user) {
    // Sacarle la password al Json acá
    fromJson(util::JsonToString(user));
}

UserProfile::UserProfile() { }

double UserProfile::getLatitude() const {
    return latitude;
}

double UserProfile::getLongitude() const {
    return longitude;
}

std::string UserProfile::getName() const {
    return name;
}

void UserProfile::parseInterests(Json::Value &user) {
    Json::Value userInterests = user["user"]["interests"];
    int interestsSize = userInterests.size();
    for (int i = 0; i < interestsSize; i++) {
        Json::Value interest = userInterests[i];
        interestList.insert(Interest(interest));
    }
}

std::string UserProfile::getId() const {
    return id;
}

const InterestList &UserProfile::getInterests() {
    return interestList;
}

std::string UserProfile::getEmail() const {
    return email;
}

Json::Value UserProfile::getJson() const {
    return user;
}

void UserProfile::fromJson(std::string user_str) {
    user = util::stringToJson(user_str);
    if(!user["user"].isMember("name")) throw Json::Exception("Missing \"name\" field!");
    if(!user["user"].isMember("alias")) throw Json::Exception("Missing \"alias\" field!");
    if(!user["user"].isMember("email")) throw Json::Exception("Missing \"email\" field!");
    if(!user["user"].isMember("interests")) throw Json::Exception("Missing \"interests\" field!");
    name = user["user"]["name"].asString();
    email = user["user"]["email"].asString();
    parseInterests(user);
}

void UserProfile::changeId(std::string userId) {
    user["user"]["id"] = userId;
    id = userId;
}







