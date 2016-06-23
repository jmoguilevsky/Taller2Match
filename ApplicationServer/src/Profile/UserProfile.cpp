//
// Created by chris on 26/03/16.
//

#include "UserProfile.h"
#include "../Utilities/util.h"
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

void UserProfile::parseInterests(Json::Value &user) {
    Json::Value userInterests = user["user"]["interests"];
    int interestsSize = userInterests.size();
    for (int i = 0; i < interestsSize; i++) {
        Json::Value interest = userInterests[i];
        if(interest["category"].asString() == "sex"){
            sexInterest = interest["value"].asString();
        } else {
            interestList . insert(Interest(interest));
        }
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
    user.removeMember("info");
    if(!user["user"].isMember("name")) throw Json::Exception("Missing \"name\" field!");
    if(!user["user"].isMember("alias")) throw Json::Exception("Missing \"alias\" field!");
    if(!user["user"].isMember("email")) throw Json::Exception("Missing \"email\" field!");
    if(!user["user"].isMember("interests")) throw Json::Exception("Missing \"interests\" field!");
    if(!user["user"].isMember("sex")) throw Json::Exception("Missing \"sex\" field!");
    name = user["user"]["name"].asString();
    email = user["user"]["email"].asString();
    sex = user["user"]["sex"].asString();
    user["user"]["photo_profile"] = "asdasdkjgfkygfkhgkjhgkjhgkjhgkjhgkhgkjhgkjhgkjhgkhgkjgk";
    parseInterests(user);

}

void UserProfile::changeId(std::string userId) {
    user["user"]["id"] = userId;
    id = userId;
}

std::string UserProfile::getSex() {
    return sex;
}

std::string UserProfile::getSexInterest() {
    return sexInterest;
}







