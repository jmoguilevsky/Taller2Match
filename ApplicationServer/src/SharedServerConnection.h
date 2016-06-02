//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_SHAREDSERVERCONNECTION_H
#define APPSERVER_SHAREDSERVERCONNECTION_H

#include "json/json.h"
#include "Mongoose/MgHTTPClient.h"
#include "HTTP/HTTPRequest.h"
#include "HTTP/HTTPResponse.h"
#include "SharedData.h"

//! Una conexión hacia el Shared Server

class SharedServerConnection : public SharedData {

    std::string sharedAddress;

public:

    SharedServerConnection(std::string sharedAddress);

    bool getUsersList(vector<UserProfile>* users);

    bool getUserProfile(std::string sharedId, UserProfile* userProfile);

    bool newUser(UserProfile userProfile, std::string* sharedId);

    bool updateProfile(string basic_string, UserProfile profile);


};

#endif //APPSERVER_SHAREDSERVERCONNECTION_H
