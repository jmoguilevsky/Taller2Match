//
// Created by chris on 27/04/16.
//

#include "SharedServerConnection.h"
#include "utils.h"
#include <iostream>
#include <fstream>

SharedServerConnection::SharedServerConnection(std::string sharedAddress) {
	this->sharedAddress = sharedAddress;
}

std::vector<UserProfile> SharedServerConnection::getUsersList() {
	MgHTTPClient c;
	bool a = c.connectToUrl(sharedAddress);
	std::map<std::string, std::string> headers;
	headers["Host"] = sharedAddress;
	HTTPRequest request("GET", "/users", headers, "");
	HTTPResponse response = c.sendRequest(request);
	Json::Value usersList = utils::stringToJson(response.getBody());
	std::vector<UserProfile> users;

	for (int i = 0; i < usersList["users"].size(); i++) {
		UserProfile profile(usersList["users"][i]);
		users.push_back(profile);
	}

	return users;
}

UserProfile SharedServerConnection::getUserProfile(std::string user) {
	MgHTTPClient c;
	c.connectToUrl(sharedAddress);
	std::map<std::string, std::string> headers;
	headers["Host"] = sharedAddress;

	HTTPRequest request("GET", "/users/" + user, headers, "");
	HTTPResponse response = c.sendRequest(request);

	Json::Value userProfile = utils::stringToJson(response.getBody());

	return userProfile;
}

int SharedServerConnection::newUser(UserProfile &userProfile) {
	MgHTTPClient c;
	c.connectToUrl(sharedAddress);
	std::map<std::string, std::string> headers;
	headers["Host"] = "enigmatic-depths-58073.herokuapp.com";
	headers["Content-Type"] = "application/json";
	headers["Cache-Control"] = "no-cache";
	std::string profile = utils::JsonToString(userProfile.getJson());
	std::stringstream s;

	s << profile.size();
	std::string t;
	s >> t;


	headers["Content-Length"] = t;
	HTTPRequest request("POST", "/users", headers, profile);

	HTTPResponse response = c.sendRequest(request);

	return response.getCode(); //????
}