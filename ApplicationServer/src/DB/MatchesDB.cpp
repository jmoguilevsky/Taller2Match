//
// Created by chris on 24/04/16.
//

#include <iostream>
#include "MatchesDB.h"
#include "JsonList.h"

bool valueExists(NoSQLDatabase &db, std::string key, std::string value) {
	std::string values;
	db.get(key, values);
	Json::Value list(values);
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == key) { return true; }
	}
	return false;
}

void append(NoSQLDatabase &db, std::string key, std::string value) {
	std::string values;
	db.get(key, values);
	Json::Value valueJson(value);
	Json::Value list(values);
	list.append(valueJson);
	db.save(key, utils::JsonToString(list));
}

int MatchesDB::likeUser(const std::string &user1, const std::string &user2) {

	if (valueExists(noMatches, user1, user2)) {
		std::cout << "Already in no matches! " << std::endl;
		return 0;
	}

	if (valueExists(likes, user1, user2)) {
		std::cout << "Already in likes! " << std::endl;
		return 0;
	}

	append(likes, user1, user2);

	append(likesReceived, user2, user1); // O solamente mantener la cantidad

	if (valueExists(likes, user2, user1)) {
		std::cout << "Match!" << std::endl;

		append(matches, user1, user2);
		append(matches, user2, user1);

	}

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

	append(noMatches, user1, user2);

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

