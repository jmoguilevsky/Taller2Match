//
// Created by chris on 27/04/16.
//

#include "SharedServerConnection.h"
#include "utils.h"

SharedServerConnection::SharedServerConnection(std::string sharedAddress) {
	this->sharedAddress = sharedAddress;
}

Json::Value SharedServerConnection::getUsersList() {
	HTTPRequestSender c(sharedAddress);
	HTTPRequest request("GET", "/users", "");
	HTTPResponse response = c.sendRequest(request);
	Json::Value usersList = utils::stringToJson(response.getBody());
	return usersList;
}

Json::Value SharedServerConnection::getUserProfile(std::string user) {
	// TODO es prácticamente idéntico al getUsersList!!!
	HTTPRequestSender c(sharedAddress);
	HTTPRequest request("GET", "/users/" + user, "");
	HTTPResponse response = c.sendRequest(request);
	Json::Value userProfile = utils::stringToJson(response.getBody());
	return userProfile;
}

Json::Value SharedServerConnection::newUser(Json::Value &userProfile) {

}