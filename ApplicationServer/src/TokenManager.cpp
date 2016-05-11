//
// Created by chris on 27/04/16.
//

#include <iostream>
#include "TokenManager.h"

std::string TokenManager::getNewToken(std::string username) {
	std::string token = username;
	// TODO ver cómo se fabrican los tokens.
	tokens[username] = username;
	return token;
}

bool TokenManager::isValid(std::string username, std::string token) {
	return tokens.count(username) == 1 && tokens[username] == token;
}

void TokenManager::invalidateToken(std::string username, std::string token) {
	tokens[username] = "";
}