//
// Created by chris on 24/04/16.
//

#include "SignUp.h"
#include "../json/json.h"
#include "../utils.h"

#define USER_ALREADY_EXISTS_PHRASE "Conflict"

#define USER_CREATED_OK_PHRASE "OK"

HTTPResponse SignUp::handle() {
	Json::Value signUpData = utils::stringToJson(request.getBody());
	std::string username = signUpData["email"].asString();
	std::string password = signUpData["password"].asString();
	int ret = db.newUser(username, password);
	// TODO en realidad, acá debería ver si el shared ya le da un perfil de usuario con
	// TODO ese username/mail. Entonces, el usuario ya existe y no se puede crear.
	std::map<std::string, std::string> headers;
	std::string code;
	std::string phrase;
	std::string body;
	headers["Content-type"] = "application/json";
	if (ret == USER_ALREADY_EXISTS) {
		code = "409";
		phrase = USER_ALREADY_EXISTS_PHRASE;
		body = "{\"error\":\"User already exists\"}";
	} else if (ret == USER_CREATED_OK) {
		code = "XXX";
		phrase = USER_CREATED_OK_PHRASE;
		body = request.getBody();
	}
	std::cout << "Signed up OK " << std::endl;

	return HTTPResponse(code, phrase, headers, body);
}

SignUp::SignUp(HTTPRequest request, LoginDB &db) : RequestHandler(request),
                                                   db(db) {
}