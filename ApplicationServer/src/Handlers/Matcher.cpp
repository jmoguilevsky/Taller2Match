//
// Created by chris on 24/04/16.
//

#include <iostream>
#include <set>
#include <algorithm>
#include "Matcher.h"
#include "../UserProfile.h"

int calculateDistance(UserProfile &profile, UserProfile &userProfile);

std::vector<UserProfile> Matcher::getMatches(std::string email) {
	std::vector<UserProfile> s;
	return s;
}

void Matcher::buildUserProfiles(std::map<std::string, UserProfile> &candidates) {
	std::vector<UserProfile> users = sharedData.getUsersList();
}

std::vector<UserProfile> Matcher::getCandidates(std::string email) {
	std::vector<UserProfile> s;
	return s;
}

bool comp(const std::pair<UserProfile, int> &a, const std::pair<UserProfile, int> &b) {
	return a.second > b.second;
}

int Matcher::calculateDistance(UserProfile &userA, UserProfile &userB) {
	// Calcula la distancia entre los dos usuarios.
	return 0;
}

int Matcher::calculateScore(UserProfile &userA, UserProfile &userB) {
	// Calcula el "score" que tiene el match userA - userB, según sus intereses y distancia.
	int intInCommon = getInterestsInCommon(userA, userB);
	int distance = calculateDistance(userA, userB);
	// Hacer algo con la distancia.
	int score = intInCommon - distance; // Algo que a menor distancia dé mejor puntaje.
	return score;
}


std::vector<std::pair<UserProfile, int>> Matcher::filterCandidates(std::string email,
                                                                   std::map<std::string, UserProfile> &candidates) {

	UserProfile thisUser = candidates[email];
	InterestList user1Interests = thisUser.getInterests();
	candidates.erase(email);

	//discardCandidates(candidates);

	std::vector<std::pair<UserProfile, int>> scores;
	return scores;
}

void Matcher::discardCandidates(std::map<std::string, UserProfile> &candidates) {
}

int Matcher::getInterestsInCommon(UserProfile &user1, UserProfile &user2) {
	InterestList user1Interests = user1.getInterests();
	InterestList user2Interests = user2.getInterests();
	InterestList inCommon;

	InterestList::iterator it1b = user1Interests.begin();
	InterestList::iterator it1e = user1Interests.end();
	InterestList::iterator it2b = user2Interests.begin();
	InterestList::iterator it2e = user2Interests.end();

	std::set_intersection(it1b, it1e, it2b, it2e, std::inserter(inCommon, inCommon.begin()));

	return inCommon.size();
}

Matcher::Matcher(MatchesDB &db, SharedData &sharedData) : db(db), sharedData(sharedData) {
}


int Matcher::postNoMatch(std::string emailA, std::string emailB) {
	return 0;
}

int Matcher::postLike(std::string emailA, std::string emailB) {
	return 0;
}



