//
// Created by chris on 27/04/16.
//

#include "SharedServerConnection.h"

SharedServerConnection::SharedServerConnection(std::string sharedAddress) {
	this->sharedAddress = sharedAddress;
}

Json::Value SharedServerConnection::getUsersList() {
	return Json::Value();
}

Json::Value SharedServerConnection::getUserProfile(std::string user) {
	return Json::Value();
}

Json::Value SharedServerConnection::newUser(Json::Value &userProfile) {
	return Json::Value();
}