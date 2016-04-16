//
// Created by chris on 12/04/16.
//

#include "DBManager.h"
#include <iostream>
#include <sstream>
#include <vector>

DB* DBManager::likes;
DB* DBManager::matches;
DB* DBManager::noMatches;

void DBManager::initDBs(const std::string &likesDBName,
                        const std::string &matchesDBName,
                        const std::string &noMatchesDBName) {
	// Crear/abrir las bases de datos
	likes = new DB(likesDBName);
	matches = new DB(matchesDBName);
	noMatches = new DB(noMatchesDBName);
	// TODO ver el tema de los nombres
}

int DBManager::likeUser(const std::string &user1, const std::string &user2) {
	// TODO return defines según cómo queda la cosa.

	if(!utils::valueInDBList(noMatches,user1,user2)){
		utils::appendValue(likes,user1,user2);
	}
	if(utils::valueInDBList(likes,user1,user2) && utils::valueInDBList(likes,user2,user1)){
		utils::appendValue(matches,user1,user2);
		utils::appendValue(matches,user2,user1);
	}
	return 0;
}

int DBManager::rejectUser(const std::string &user1, const std::string &user2){
	if(!utils::valueInDBList(likes,user1,user2) && !utils::valueInDBList(matches,user1,user2)){
		utils::appendValue(noMatches,user1,user2);
	}
	// TODO valor de retorno?
	return 0;
}

std::vector<std::string> DBManager::getLikes(const std::string &user){
	return utils::valuesAsVector(likes,user);
}

std::vector<std::string> DBManager::getMatches(const std::string &user) {
	// Devuelve los matches para el usuario.
	return utils::valuesAsVector(matches,user);
}

std::vector<std::string> DBManager::getNoMatches(const std::string &user){
	// Devuelve los users que user rechazó.
	return utils::valuesAsVector(noMatches,user);
}


void DBManager::closeDBs(){
	//Cerrar las bases de datos
	delete likes;
	delete matches;
	delete noMatches;
}