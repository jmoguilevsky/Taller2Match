//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_SHAREDSERVERCONNECTION_H
#define APPSERVER_SHAREDSERVERCONNECTION_H

#include "../json/json.h"
#include "../Mongoose/MgHTTPClient.h"
#include "../HTTP/HTTPRequest.h"
#include "../HTTP/HTTPResponse.h"
#include "SharedProfilesDatabase.h"
#include "../Profile/UserProfile.h"

//! Una conexión hacia el Shared Server

class SharedServerConnection : public SharedProfilesDatabase {

    std::string sharedAddress;

public:

    SharedServerConnection(std::string sharedAddress);

    vector<UserProfile> getUsersList();

    UserProfile getUserProfile(std::string sharedId);

    std::string newUser(UserProfile userProfile);

    void updateProfile(string basic_string, UserProfile profile);

    std::vector<Interest> getAllInterests();
};

#endif //APPSERVER_SHAREDSERVERCONNECTION_H
