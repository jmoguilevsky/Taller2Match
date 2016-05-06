//
// Created by chris on 26/03/16.
//

#include "UserProfile.h"
#include "utils.h"
#include <iostream>

UserProfile::UserProfile(Json::Value &user) {
	id = user["id"].asString();
	name = user["name"].asString();
	parseInterests(user);
/*	Json::Value jsonLocation = user["location"];
	Json::Value jsonLatitude = jsonLocation["latitude"];
	Json::Value jsonLongitude = jsonLocation["longitude"];
	latitude = std::stod(jsonLatitude.asString());
	longitude = std::stod(jsonLongitude.asString());
 */
}

UserProfile::UserProfile() { }
UserProfile::UserProfile(const UserProfile &user) {
	id = user.id;
	name = user.name;
	latitude = user.latitude;
	longitude = user.longitude;
}

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
		std::vector<std::string> &interestsInCategory = interestsMap[interest["category"].asString()];
		interestsInCategory.push_back(interest["value"].asString());
	}
}

std::string UserProfile::getId() const {
	return id;
}

const InterestMap &UserProfile::getInterests() const {
	return interestsMap;
}