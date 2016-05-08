//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHESDB_H
#define APPSERVER_MATCHESDB_H

#include <string>
#include <vector>
#include "RocksDB.h"
#include "../utils.h"

//! Manejo de las bases de datos relacionadas con los likes y los matches.
class MatchesDB {
	NoSQLDatabase& noMatches;
	NoSQLDatabase& likes;
	NoSQLDatabase& matches;
public:
	MatchesDB(NoSQLDatabase& noMatches, NoSQLDatabase& likes, NoSQLDatabase& matches);

	int likeUser(const std::string &user1, const std::string &user2);

	std::vector<std::string> getLikes(const std::string &user);

	std::vector<std::string> getMatches(const std::string &user);

	std::vector<std::string> getNoMatches(const std::string &user);

	bool userMatch(std::string userA, std::string userB);

	int getLikesReceived(const std::string &user);

	int rejectUser(const std::string &user1, const std::string &user2);
};


#endif //APPSERVER_MATCHESDB_H
