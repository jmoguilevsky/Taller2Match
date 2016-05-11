//
// Created by chris on 24/04/16.
//

#include <fstream>
#include "Login.h"
#include "../utils.h"

int Login::login(std::string email, std::string password, std::string &token) {
	int ret = db.login(email, password);
	std::cout << "EMAIL & PASS OK: " << (ret ? "OK" : "NO") << std::endl;
	token = tokenManager.getNewToken(email);
	return ret;
}