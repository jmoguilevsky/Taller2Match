//

#include <iostream>
#include <set>
#include <algorithm>
#include <list>
#include "Matcher.h"

#define DAILY_CANDIDATES 10

int Matcher::postLikeLastCandidate(std::string userId) {
    std::string candidates;
    candidates_db -> get (userId, candidates);
    Json::Value array = util::stringToJson(candidates);
    Json::Value lastCandidateJson;
    array.removeIndex(0,&lastCandidateJson);
    candidates_db -> save(userId, util::JsonToString(array));
    Json::Value lastCandidateId = lastCandidateJson["user"]["id"];
    append(*likes_db, userId,lastCandidateId);
    Json::Value thisUserId = userId;
    std::string lastId = lastCandidateId.asString();
    append(*likesReceived_db, lastId, thisUserId);

    if (valueExists(*likes_db,lastId, userId)) {
        append(*matches_db, userId, lastCandidateId);
        append(*matches_db, lastId, thisUserId);
    }

    return 0;
}

int Matcher::postDislike(std::string userId) {
    std::string candidates;
    candidates_db -> get (userId, candidates);
    Json::Value array = util::stringToJson(candidates);
    Json::Value lastCandidateJson;
    array.removeIndex(0,&lastCandidateJson);
    candidates_db -> save(userId, util::JsonToString(array));
    Json::Value lastCandidateId = lastCandidateJson["user"]["id"];
    append(*dislikes_db, userId,lastCandidateId);
    return 0;
}

int Matcher::getLikesReceived(const std::string &user) {
    std::string list;
    likesReceived_db->get(user, list);
    Json::Value listJson = util::stringToJson(list);
    return listJson.size();
}

std::string Matcher::getLikes(const std::string &user) {
    std::string sLikes;
    likes_db->get(user, sLikes);
    return sLikes;
}

std::string Matcher::getMatches(const std::string &user) {
    std::string myMatches;
    matches_db->get(user, myMatches);
    return myMatches;
}

std::vector<std::string> Matcher::getDislikes(const std::string &user) {
    // Devuelve los users que user rechazó.
    /*return util::valuesAsVector(noMatches, user);*/
    return std::vector<std::string>();
}

std::vector<UserProfile> Matcher::getMatches(std::string email) {
    std::vector<UserProfile> s;
    return s;
}

UserProfile Matcher::getNextCandidate(std::string userId) {

    std::string lastTimeStr;
    limit_db->get(userId, lastTimeStr);
    tm lastTime = util::stringToDate(lastTimeStr);
    tm today = util::currentDate();
    time_t t1 = mktime(&lastTime);
    time_t t2 = mktime(&today);
    if (difftime(t2, t1) > 0) {
        // Pasó más de un día desde la última vez que se buscaron los candidatos
        // Busco candidatos otra vez
        std::vector<UserProfile> newCandidates = calculateCandidates(userId);
        Json::Value array;
        for (int i = 0; i < newCandidates.size(); i++) {
            array.append(newCandidates[i].getJson());
        }
        candidates_db -> save(userId,array.asString());
    }
    else {
        // Si es el mismo día, mando el siguiente candidato, entre los no likeados.
        std::string candidates;
        candidates_db -> get (userId, candidates);
        Json::Value array = util::stringToJson(candidates);
        UserProfile nextCandidate;
        nextCandidate.fromJson(util::JsonToString(array[0]));
        return nextCandidate;
    }

    std::vector<UserProfile> users;
    sharedData.getUsersList(&users);
    // Descartar los usuarios que no están registrados en este app server?
    int numberOfCandidates = 3;
    std::vector<UserProfile> returnUsers;
    for (int i = 0; i < numberOfCandidates; i++) {
        UserProfile user;
        do {
            user = users[rand() % users.size()];
        }
        while (user.getEmail() == userId);
        returnUsers.push_back(user);
    }
    return UserProfile();
}

bool comp(const std::pair<UserProfile, int> &a, const std::pair<UserProfile, int> &b) {
    return a.second > b.second;
}

int Matcher::calculateDistance(UserProfile &userA, UserProfile &userB) {
    // Calcula la distancia entre los dos usuarios.
    return 0;
}


int Matcher::calculateScore(UserProfile &userId, UserProfile &otherUserId) {
    // Calcula el "score" que tiene el match userA - userB, según sus intereses y distancia.
    int intInCommon = getInterestsInCommon(userId, otherUserId);
    int distance = calculateDistance(userId, otherUserId);
    // Hacer algo con la distancia.
    int score = intInCommon - distance; // Algo que a menor distancia dé mejor puntaje.
    return score;
}

std::vector<UserProfile> Matcher::candidatesLeft(std::string userId) {
    std::string candidates;
    candidates_db->get(userId, candidates);
    Json::Value candidatesJson = util::stringToJson(candidates);
    std::vector<UserProfile> candidatesProfiles;

    for (int i = 0; i < candidatesJson.size(); i++) {
        UserProfile candidate(candidatesJson[i]);
        candidatesProfiles.push_back(candidate);
    }

    return candidatesProfiles;
}

std::vector<UserProfile> Matcher::calculateCandidates(std::string userId) {

    std::vector<UserProfile> candidates;
    sharedData.getUsersList(&candidates);
    UserProfile userProfile;

    for (std::vector<UserProfile>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
        if (it->getId() == userId) {
            userProfile = *it;
            candidates.erase(it);
            break;
        }
    }

    std::map<std::string, int> scores;

    discardCandidates(userId, candidates);

    for (std::vector<UserProfile>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
        UserProfile otherUserProfile = *it;
        std::string otherUserId = otherUserProfile.getId();
        scores[otherUserId] = calculateScore(userProfile, otherUserProfile);
    }

    // TODO ordenarlos por score y devolver DAILY_CANDIDATES

    std::vector<UserProfile> score;
    return score;
}

void Matcher::discardCandidates(std::string userId, std::vector<UserProfile> &candidates) {
    std::vector<UserProfile> finalCandidates;
    for (int i = 0; i < candidates.size(); i++) {
        std::string id = candidates[i].getId();
        if (!valueExists(*likes_db, userId, id) || !valueExists(*dislikes_db, userId, id) ||
            !valueExists(*matches_db, userId, id)) {
            finalCandidates.push_back(candidates[i]);
        }
    }
    candidates = finalCandidates;
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

    return (int)inCommon.size();
}

bool Matcher::usersMatch(std::string userId, std::string otherUserId) const {
    return valueExists(*matches_db, userId, otherUserId);
}