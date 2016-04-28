//
// Created by chris on 26/03/16.
//

#include "UserProfile.h"
#include <iostream>

UserProfile::UserProfile(Json::Value &user) {
	id = user["id"].asString();
	name = user["name"].asString();
	getInterestsForCategory(user, "music/band", musicBandInterests);
	getInterestsForCategory(user, "sport", sportInterests);
	getInterestsForCategory(user, "food", foodInterests);
	Json::Value jsonLocation = user["location"];
	Json::Value jsonLatitude = jsonLocation["latitude"];
	Json::Value jsonLongitude = jsonLocation["longitude"];
	latitude = std::stod(jsonLatitude.asString());
	longitude = std::stod(jsonLongitude.asString());
}

UserProfile::UserProfile() { }
UserProfile::UserProfile(const UserProfile &user) {
	id = user.id;
	name = user.name;
	latitude = user.latitude;
	longitude = user.longitude;
	musicBandInterests = user.musicBandInterests;
	sportInterests = user.sportInterests;
	foodInterests = user.foodInterests;

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

std::vector<std::string> UserProfile::getMusicBandInterests() const {
	return musicBandInterests;
}

std::vector<std::string> UserProfile::getSportInterests() const {
	return sportInterests;
}

std::vector<std::string> UserProfile::getFoodInterests() const {
	return foodInterests;
}

std::vector<std::string> UserProfile::getInterestsForCategory(Json::Value &user,
                                                              std::string category,
                                                              std::vector<std::string> &interestsList) {
	Json::Value userInterests = user["interests"];
	int interestsSize = userInterests.size();
	for (int i = 0; i < interestsSize; i++) {
		Json::Value interest = userInterests[i];
		if (interest["category"].asString() == category) {
			interestsList.push_back(interest["value"].asString());
		}
	}
	return interestsList;
}

std::string UserProfile::getId() const {
	return id;
}
