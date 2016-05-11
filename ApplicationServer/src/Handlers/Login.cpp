//
// Created by chris on 24/04/16.
//

#include <fstream>
#include "Login.h"
#include "../utils.h"

int Login::login(std::string email, std::string password, std::string &token) {
	int emailPwdOK = db.login(email, password);
	int status = 0;
	if (emailPwdOK == LOGIN_OK) {
		if (isConnected(email)) {
			status = ALREADY_LOGGED_IN;
		} else {
			token = newToken(email);
			status = LOGIN_OK;
		}
	} else {
		status = LOGIN_ERROR;
	}
	return status;
}

bool Login::isConnected(std::string email) {
	return connected.count(email);
}

void Login::invalidateToken(std::string email) {
	connected.erase(email);
}

std::string Login::newToken(std::string email) {
	std::string token = email;
	connected[email] = email;
	return token;
}

void Login::logout(std::string email) {
	invalidateToken(email);
}

bool Login::checkToken(std::string email, std::string token) {
	return connected.count(email) == 1 && connected[email] == token;
}