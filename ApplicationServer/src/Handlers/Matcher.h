//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "../DB/MatchesDB.h"
#include "../SharedData.h"
#include "../UserProfile.h"

//! Handler para todo lo relacionado con likes, matches, etc.

class Matcher {

private:

	MatchesDB &db;
	SharedData &sharedData;

public:
	Matcher(MatchesDB &db, SharedData &data);

	std::vector<UserProfile> getCandidates(std::string email);

	std::vector<UserProfile> getMatches(std::string email);

	int postLike(std::string emailA, std::string emailB);

	int postNoMatch(std::string emailA, std::string emailB);

private:
	int getInterestsInCommon(UserProfile &user1, UserProfile &user2);

	void discardCandidates(std::map<std::string, UserProfile> &candidates);

	int calculateScore(UserProfile &userA, UserProfile &userB);

	int calculateDistance(UserProfile &userA, UserProfile &userB);

	void buildUserProfiles(std::map<std::string, UserProfile> &candidates);

	std::vector<std::pair<UserProfile, int>> filterCandidates(std::string email,
	                                                          std::map<std::string, UserProfile> &candidates);
};

#endif //APPSERVER_MATCHER_H
