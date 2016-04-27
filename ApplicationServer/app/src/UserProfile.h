//
// Created by chris on 26/03/16.
//

#ifndef JSONTEST_USER_H
#define JSONTEST_USER_H

#include <vector>
#include <string>
#include "json/json.h"

typedef std::vector<std::string> InterestList;

//! Representa el perfil de un usuario y métodos para consulta de distintos campos del mismo.
class UserProfile {


	InterestList musicBandInterests;
	InterestList sportInterests;
	InterestList foodInterests;
	std::string name;
	std::string id;

public:
	UserProfile(const UserProfile &user);

	//! Crea un perfil de usuario a partir de un objeto Json.
	UserProfile(Json::Value &user);

	std::string getName() const;

	InterestList getMusicBandInterests() const;

	InterestList getSportInterests() const;

	InterestList getFoodInterests() const;

	std::string getId() const;

	double getLatitude() const;

	double getLongitude() const;

private:

	InterestList getInterestsForCategory(Json::Value &user,
	                                     std::string category,
	                                     std::vector<std::string> &interestsList);

	double latitude;
	double longitude;
};


#endif //JSONTEST_USER_H
