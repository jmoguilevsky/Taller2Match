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

	Json::Value getUsersList();

	Json::Value getUserProfile(std::string user);

	Json::Value newUser(Json::Value &userProfile);

};

#endif //APPSERVER_SHAREDSERVERCONNECTION_H
