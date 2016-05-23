//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_SHAREDDATA1_H
#define APPSERVER_SHAREDDATA1_H


#include "json/json.h"
#include "UserProfile.h"

//! Se puede "simular" la conexión al shared con una clase que implemente estos métodos.

#include <vector>
using namespace std;

class SharedData {

public:
    virtual bool getUsersList(vector<UserProfile>* users) = 0;

    virtual bool getUserProfile(std::string sharedId, UserProfile* userProfile) = 0;

    virtual bool newUser(UserProfile userProfile, std::string* sharedId) = 0;
};


#endif //APPSERVER_SHAREDDATA1_H
