//
// Created by chris on 26/03/16.
//

#ifndef JSONTEST_USER_H
#define JSONTEST_USER_H

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include "json/json.h"
#include "Interest.h"

typedef std::set<Interest> InterestList;

//! Representa el perfil de un usuario y métodos para consulta de distintos campos del mismo.
class UserProfile {
	std::string name;
	std::string id;
	InterestList interestList;

public:

	const InterestList &getInterests();

	UserProfile();
//	UserProfile(const UserProfile &user);

	//! Crea un perfil de usuario a partir de un objeto Json.
	UserProfile(Json::Value &user);

	std::string getName() const;

	std::string getId() const;

	double getLatitude() const;

	double getLongitude() const;

	std::string getEmail() const;

	Json::Value getJson() const;

	void fromJson(Json::Value user);

private:

	double latitude;
	double longitude;

	void parseInterests(Json::Value &user);

	std::string email;

	Json::Value user;
};


#endif //JSONTEST_USER_H
