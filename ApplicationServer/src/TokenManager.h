//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_TOKENMANAGER_H
#define APPSERVER_TOKENMANAGER_H

#include <map>
#include <string>

//! Para manejar el tema de los tokenManager, crearlos, chequearlos, borrarlos, etc.
// Un token dura una sesión.
class TokenManager {
	std::map<std::string, std::string> tokens;
	// Key: username, Value: token

public:
	std::string getNewToken(std::string username);

	bool isValid(std::string username, std::string token);

	void invalidateToken(std::string username, std::string token);
};


#endif //APPSERVER_TOKENMANAGER_H
