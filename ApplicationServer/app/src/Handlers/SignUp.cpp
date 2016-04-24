//
// Created by chris on 24/04/16.
//

#include "SignUp.h"
#include "../json/json.h"

#define USER_ALREADY_EXISTS_PHRASE "USER ALREADY EXISTS"

#define USER_CREATED_OK_PHRASE "USER CREATED OK"

HTTPResponse SignUp::handle() {
	Json::Value signUpData;
	std::stringstream str(request.getBody());
	str >> signUpData;
	std::string user = signUpData["user"].asString();
	std::string pass = signUpData["pass"].asString();
	int ret = db.newUser(user, pass);
	std::map<std::string, std::string> headers;
	std::string code;
	std::string phrase;
	std::string body;
	if (ret == USER_ALREADY_EXISTS) {
		code = "200";
		phrase = USER_ALREADY_EXISTS_PHRASE;
	} else if (ret == USER_CREATED_OK) {
		code = "XXX";
		phrase = USER_CREATED_OK_PHRASE;
	}
	return HTTPResponse(code, phrase, headers, body);
}

