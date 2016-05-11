//
// Created by chris on 26/03/16.
//

#include "UserProfile.h"
#include "utils.h"
#include <iostream>

UserProfile::UserProfile(Json::Value &user) {
	// Sacarle la password al Json acá
	this->user = user;
	id = user["id"].asString();
	name = user["name"].asString();
	email = user["email"].asString();
	parseInterests(user);
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
	Json::Value userInterests = user["interests"];
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

void UserProfile::fromJson(Json::Value user) {
	Json::Value p;
	p["user"] = user;
	p["user"].removeMember("password");
	this->user = p;
	//id = user["id"].asString();
	name = user["name"].asString();
	email = user["email"].asString();
	parseInterests(user);
}





