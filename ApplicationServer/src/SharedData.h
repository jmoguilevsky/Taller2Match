//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_SHAREDDATA1_H
#define APPSERVER_SHAREDDATA1_H


#include "json/json.h"
#include "UserProfile.h"

//Se puede "simular" la conexión al shared

class SharedData {

public:
	virtual std::vector<UserProfile> getUsersList() = 0;

	virtual UserProfile getUserProfile(std::string user) = 0;

	virtual int newUser(UserProfile &userProfile) = 0;
};


#endif //APPSERVER_SHAREDDATA1_H
