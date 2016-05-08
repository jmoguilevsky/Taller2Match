//
// Created by chris on 26/03/16.
//

#ifndef JSONTEST_USER_H
#define JSONTEST_USER_H

#include <vector>
#include <string>
#include "json/json.h"

typedef std::vector<std::string> InterstCategory;
typedef std::map<std::string, InterstCategory> InterestMap;

//! Representa el perfil de un usuario y métodos para consulta de distintos campos del mismo.
class UserProfile {
	std::string name;
	std::string id;
	InterestMap interestsMap;

public:

	const InterestMap &getInterests() const;

	UserProfile();
	UserProfile(const UserProfile &user);

	//! Crea un perfil de usuario a partir de un objeto Json.
	UserProfile(Json::Value &user);

	std::string getName() const;

	std::string getId() const;

	double getLatitude() const;

	double getLongitude() const;

private:

	double latitude;
	double longitude;

	void parseInterests(Json::Value &user);
};


#endif //JSONTEST_USER_H
