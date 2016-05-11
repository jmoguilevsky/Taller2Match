//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_SHAREDSERVERCONNECTION_H
#define APPSERVER_SHAREDSERVERCONNECTION_H

#include "json/json.h"
#include "mongoose-master/MgHTTPClient.h"
#include "HTTP/HTTPRequest.h"
#include "HTTP/HTTPResponse.h"
#include "SharedData.h"

//! Una conexión hacia el Shared MgServer
class SharedServerConnection : public SharedData {

	std::string sharedAddress;

public:

	SharedServerConnection(std::string sharedAddress);

	std::vector<UserProfile> getUsersList();

	UserProfile getUserProfile(std::string user);

	int newUser(UserProfile &userProfile);

};

#endif //APPSERVER_SHAREDSERVERCONNECTION_H
