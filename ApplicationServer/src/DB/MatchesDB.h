//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHESDB_H
#define APPSERVER_MATCHESDB_H

#include <string>
#include <vector>
#include "DB.h"
#include "../utils.h"

//! Manejo de las bases de datos relacionadas con los likes y los matches.
class MatchesDB {
	DB noMatches;
	DB likes;
	DB matches;
public:
	MatchesDB() : noMatches("noMatches"), likes("likes"), matches("matches") { }

	int likeUser(const std::string &user1, const std::string &user2);

	std::vector<std::string> getLikes(const std::string &user);

	std::vector<std::string> getMatches(const std::string &user);

	std::vector<std::string> getNoMatches(const std::string &user);

	int getLikesReceived(const std::string &user);

	int rejectUser(const std::string &user1, const std::string &user2);
};


#endif //APPSERVER_MATCHESDB_H
