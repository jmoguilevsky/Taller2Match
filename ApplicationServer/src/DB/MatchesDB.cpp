//
// Created by chris on 24/04/16.
//

#include <iostream>
#include "MatchesDB.h"
#include "JsonList.h"



int MatchesDB::likeUser(const std::string &user1, const std::string &user2) {
	if (valueExists(likes, user1, user2)) {
		std::cout << "Already in likes! " << std::endl;
		return 0;
	}
	if (valueExists(noMatches, user1, user2)) {
		std::cout << "Already in no matches! " << std::endl;
		return 0;
	}
	Json::Value u2 = user2;
	append(likes, user1, u2);
	Json::Value u1 = user1;
	append(likesReceived, user2, u1); // O solamente mantener la cantidad

	if (valueExists(likes, user2, user1)) {
		append(matches, user1, u2);
		append(matches, user2, u1);
	}

	std::string likesOfUser;
	likes.get(user1, likesOfUser);
	std::cout << "Liked by " << user1 << ": " << likesOfUser << std::endl;

	std::string likesRecByUser;
	likesReceived.get(user2, likesRecByUser);
	std::cout << "Likes received by " << user2 << ": " << likesRecByUser << std::endl;

	std::string matchesA;
	matches.get(user1, matchesA);
	std::cout << "Matches of " << user1 << ": " << matchesA << std::endl;

	std::string matchesB;
	matches.get(user2, matchesB);
	std::cout << "Matches of " << user2 << ": " << matchesB << std::endl;

	return 0;
}

int MatchesDB::rejectUser(const std::string &user1, const std::string &user2) {

	if (valueExists(likes, user1, user2)) {
		std::cout << "Already in likes! " << std::endl;
		return 0;
	}
	if (valueExists(noMatches, user1, user2)) {
		std::cout << "Already in no matches! " << std::endl;
		return 0;
	}

	//append(noMatches, user1, user2);

	std::string noMatchesA;
	noMatches.get(user1, noMatchesA);
	std::cout << "No-Matches of " << user1 << ": " << noMatchesA << std::endl;


	return 0;
}

int MatchesDB::getLikesReceived(const std::string &user) {
	std::string num;
	likesReceived.get(user, num);
	int n = atoi(num.c_str());
	return n;
}

std::string MatchesDB::getLikes(const std::string &user) {
	std::string sLikes;
	likes.get(user, sLikes);
	return sLikes;
}

std::string MatchesDB::getMatches(const std::string &user) {
	std::string myMatches;
	matches.get(user, myMatches);
	return myMatches;
}

std::vector<std::string> MatchesDB::getNoMatches(const std::string &user) {
	// Devuelve los users que user rechazó.
	/*return utils::valuesAsVector(noMatches, user);*/
	return std::vector<std::string>();
}

MatchesDB::MatchesDB(NoSQLDatabase& noMatches, NoSQLDatabase& likes, NoSQLDatabase& matches)
		: noMatches(noMatches), likes(likes), matches(matches), likesReceived("likesReceived") { }

bool MatchesDB::userMatch(std::string userA, std::string userB) {
	return true;
}

