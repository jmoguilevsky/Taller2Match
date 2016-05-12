//
// Created by chris on 12/05/16.
//

#include "UsersHTTP.h"
#include "../HTTP/HTTP.h"

HTTPResponse UsersHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	std::string uri = request.getUri();

	if (verb == "POST" && uri == "/users/signup") {
		return handleSignUp(request);
	} else if (verb == "POST" && uri == "/users/login") {
		return handleLogin(request);
	} else if (verb == "POST" && uri == "/users/logout") {
		return handleLogout(request);
	} else {
		return HTTP::BadRequest();
	}
}

HTTPResponse UsersHTTP::handleSignUp(HTTPRequest request) {

	Json::Value userInfo = utils::stringToJson(request.getBody());
	std::string email = userInfo["user"]["email"].asString();
	std::string password = userInfo["user"]["password"].asString();

	UserProfile userProfile;
	userProfile.fromJson(userInfo["user"]);

	int code = users->signUp(email, password, userProfile);

	switch (code) {
		case 201:
			return HTTP::OK();
		case 400:
			return HTTP::Error("User already exists");
		default:
			return HTTP::Error("Unknown error");
	}
}

HTTPResponse UsersHTTP::handleLogin(HTTPRequest request) {

	Json::Value userInfo = utils::stringToJson(request.getBody());
	std::string email = userInfo["user"]["email"].asString();
	std::string password = userInfo["user"]["password"].asString();
	std::string token;

	int code = users->login(email, password, token);

	switch (code) {
		case LOGIN_ERROR:
			return HTTP::Error("User doesn't exist or wrong password");
		case LOGIN_OK: {
			std::string tokenJson = "{\"token\":" + token + "\"}";
			return HTTP::OKJson(tokenJson);
		}
		case ALREADY_LOGGED_IN:
			return HTTP::Error("User already logged in");
		default:
			return HTTP::Error("Unkown error");
	}
}

HTTPResponse UsersHTTP::handleLogout(HTTPRequest request) {
	std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	users->logout(email);
	return HTTP::OK();
}

bool UsersHTTP::verifyCredentials(HTTPRequest request) {
	std::string authHeader = request.getHeader("Authorization");
	Json::Value auth = utils::stringToJson(authHeader);
	std::string email = auth["email"].asString();
	std::string token = auth["token"].asString();
	return users->checkToken(email, token);
}

UsersHTTP::~UsersHTTP() {
	delete users;
}

UsersHTTP::UsersHTTP(UsersDB &usersDB, SharedData &sharedData) {
	users = new Users(usersDB, sharedData);
}