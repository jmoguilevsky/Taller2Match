//
// Created by chris on 24/04/16.
//

#include <fstream>
#include "Login.h"
#include "../utils.h"

#define LOGIN_OK_PHRASE "OK"
#define USER_DOESNT_EXIST_PHRASE "USER_DOESNT_EXIST"
#define WRONG_PASSWORD_PHRASE "WRONG_PASSWORD"

HTTPResponse Login::handle() {

	Json::Value loginData = utils::stringToJson(request.getBody());
	std::string username = loginData["email"].asString();
	std::string password = loginData["password"].asString();
	int ret = db.login(username, password);
	std::map<std::string, std::string> headers;
	std::string code;
	std::string phrase;
	std::string body;
	if (ret == LOGIN_OK) {
		code = "200";
		phrase = LOGIN_OK_PHRASE;
		Json::Value userProfileJson = sharedServer.getUserProfile(username);
		std::string userProfile = utils::JsonToString(userProfileJson);
		body = "{\"token\":\"" + tokenManager.getNewToken(username) + "\"\n" +
		       userProfile + "\n}";
	} else if (ret == USER_DOESNT_EXIST) {
		code = "XXX";
		phrase = USER_DOESNT_EXIST_PHRASE;
		body = phrase;
	} else if (ret == WRONG_PASSWORD) {
		code = "XXX";
		phrase = WRONG_PASSWORD_PHRASE;
		body = phrase;
	}
	std::cout << "Logged in OK " << std::endl;
	return HTTPResponse(code, phrase, headers, body);
}

Login::Login(HTTPRequest request, LoginDB &db,
             TokenManager &tokenManager, SharedServerConnection &sharedServer)
		: RequestHandler(
		request), db(db),
		  tokenManager(tokenManager), sharedServer(sharedServer) {
}



