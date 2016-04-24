//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHESDB_H
#define APPSERVER_MATCHESDB_H

#include <string>
#include <vector>
#include "DB.h"
#include "../utils.h"

class MatchesDB {
	DB noMatches;
	DB likes;
	DB matches;

	MatchesDB() : noMatches("noMatches"), likes("likes"), matches("matches") { }

	int likeUser(const std::string &user1, const std::string &user2);
};


#endif //APPSERVER_MATCHESDB_H
