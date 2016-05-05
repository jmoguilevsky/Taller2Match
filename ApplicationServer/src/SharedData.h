//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_SHAREDDATA1_H
#define APPSERVER_SHAREDDATA1_H


#include "json/json.h"

class SharedData {

public:
	virtual Json::Value getUsersList() = 0;

	virtual Json::Value getUserProfile(std::string user) = 0;

	virtual Json::Value newUser(Json::Value &userProfile) = 0;
};


#endif //APPSERVER_SHAREDDATA1_H
