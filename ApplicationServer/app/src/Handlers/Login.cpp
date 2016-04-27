//
// Created by chris on 24/04/16.
//

#include <fstream>
#include "Login.h"
#include "../json/json.h"
#include <iostream>

#define LOGIN_OK_PHRASE "OK"
#define USER_DOESNT_EXIST_PHRASE "USER_DOESNT_EXIST"
#define WRONG_PASSWORD_PHRASE "WRONG_PASSWORD"

HTTPResponse Login::handle() {

	Json::Value loginData;
	Json::Reader reader;
	reader.parse(request.getBody(), loginData);
	std::string user = loginData["user"].asString();
	std::string pass = loginData["pass"].asString();
	int ret = db.login(user, pass);
	std::map<std::string, std::string> headers;<
	std::string code;
	std::string phrase;
	std::string body;
	if (ret == LOGIN_OK) {
		code = "200";
		phrase = LOGIN_OK_PHRASE;
	} else if (ret == USER_DOESNT_EXIST) {
		code = "XXX";
		phrase = USER_DOESNT_EXIST_PHRASE;
	} else if (ret == WRONG_PASSWORD) {
		code = "XXX";
		phrase = WRONG_PASSWORD_PHRASE;
	}
	std::cout << "Logged in OK " << std::endl;
	return HTTPResponse(code, phrase, headers, phrase);
}

Login::Login(HTTPRequest request, LoginDB &db) : db(db) {
	this->request = request;
}

