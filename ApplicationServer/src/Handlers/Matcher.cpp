//

#include <iostream>
#include <set>
#include <algorithm>
#include <list>
#include "Matcher.h"
#include "../Date.h"

#define DAILY_CANDIDATES 10

int Matcher::postLike(std::string userId, std::string candidateId) {

    bool ok = candidates_db->has_value(userId, candidateId);
    if (!ok) return 1; //// NO ES UN CANDIDATE -> ERROR

    candidates_db->remove_value(userId, candidateId);

    likes_db->append_value(userId, candidateId);

    likesReceived_db->append_value(candidateId, userId);

    if (likes_db->has_value(candidateId, userId)) {
        // Hay match
        matches_db->append_value(userId, candidateId);
        matches_db->append_value(candidateId, userId);
    }

    return 0;
}

int Matcher::postDislike(std::string userId, std::string candidateId) {

    bool ok = candidates_db->has_value(userId, candidateId);
    if (!ok) return 1; //// NO ES UN CANDIDATE -> ERROR

    candidates_db->remove_value(userId, candidateId);

    dislikes_db->append_value(userId, candidateId);

    return 0;
}

std::vector<std::string> Matcher::getLikesReceived(const std::string &userId) {
    std::string list;
    return likesReceived_db->values(userId);
}

std::vector<std::string> Matcher::getLikes(const std::string &userId) {
    return likes_db->values(userId);
}

std::vector<std::string> Matcher::getMatches(const std::string &userId) {
    return matches_db->values(userId);
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

bool Matcher::getNextCandidate(std::string userId, UserProfile *profile) {

    std::string lastTimeStr;

    limit_db->get(userId, lastTimeStr);

    Date lastTime;

    if (lastTimeStr != "") {
        lastTime = Date(lastTimeStr);
    }

    Date today = Date::today();

    if (lastTime < today) {
        // Pasó más de un día desde la última vez que se buscaron los candidatos
        // Busco candidatos otra vez
        std::vector<UserProfile> newCandidates = calculateCandidates(userId);
        for (int i = 0; i < newCandidates.size(); i++) {
            std::string id = newCandidates[i].getId();
            candidates_db->append_value(userId, id);
        }
        limit_db->save(userId, today.str());
    }
    // Si es el mismo día, mando el siguiente candidato, entre los no likeados.

    std::vector<std::string> candidates = candidates_db->values(userId);

    if (candidates.size() == 0) return false;
    std::string nextId = candidates[0];
    std::cout << "ID: " << nextId << std::endl;
    usersProfiles.getProfile(nextId, profile);
    return true;
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

std::vector<std::pair<std::string, int>> sortDescByValue(std::map<std::string, int> mmap) {
    std::vector<std::pair<std::string, int>> pairs;
    for (auto itr = mmap.begin(); itr != mmap.end(); ++itr)
        pairs.push_back(*itr);
    std::sort(pairs.begin(), pairs.end(), [=](std::pair<std::string, int> a, std::pair<std::string, int> b) {
                  return a.second > b.second;
              }
    );
    return pairs;

};

void Matcher::discardCandidates(std::string userId, std::map<std::string, UserProfile> &candidates) {
    std::vector<std::string> likes = likes_db->values(userId);
    for (int i = 0; i < likes.size(); i++) {
        std::string candidateId = likes[i];
        if (candidates.count(candidateId) == 1) {
            candidates.erase(candidateId);
        }
    }
    std::vector<std::string> dislikes = dislikes_db->values(userId);
    for (int i = 0; i < dislikes.size(); i++) {
        std::string candidateId = dislikes[i];
        if (candidates.count(candidateId) == 1) {
            candidates.erase(candidateId);
        }
    }
}

std::vector<UserProfile> Matcher::calculateCandidates(std::string userId) {

    std::map<std::string, UserProfile> candidates;
    usersProfiles.getUsers(&candidates);
    UserProfile userProfile = candidates[userId];
    candidates.erase(userId);

    // ***** Descarto los candidatos que ya estan en likes y dislikes

    discardCandidates(userId, candidates);

    // ***** Calculo el "puntaje" para cada usuario

    std::map<std::string, int> scores;

    for (std::map<std::string, UserProfile>::iterator it = candidates.begin();
         it != candidates.end(); ++it) {
        UserProfile candidateProfile = it->second;
        std::string candidateId = candidateProfile.getId();
        scores[candidateId] = calculateScore(userProfile, candidateProfile);
    }

    // TODO ordenarlos por score y devolver DAILY_CANDIDATES (siempre que haya esa cantidad)

    std::vector<std::pair<std::string, int>> orderedByScore = sortDescByValue(scores);

    // Agarrar los DAILY_LIMIT con más puntaje

    std::vector<UserProfile> newCandidates;
    int nCand = candidates.size() < DAILY_CANDIDATES ? candidates.size() : DAILY_CANDIDATES;
    for (int i = 0; i < nCand; i++) {
        std::string candidateId = orderedByScore[i].first;
        UserProfile candidateProfile = candidates[candidateId];
        newCandidates.push_back(candidateProfile);
    }
    return newCandidates;
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

    return (int) inCommon.size();
}

Matcher::Matcher(UsersProfiles &users) : usersProfiles(users) {
    candidates_db = new JsonArrayDb("candidates");
    likesReceived_db = new JsonArrayDb("likesReceived"); // Guarda la cantidad de liks que recibió cada usuario.
    likes_db = new JsonArrayDb("likes"); // Guarda todos los usuarios que likeo cada usuario.
    dislikes_db = new JsonArrayDb("dislikes"); // Guarda todos los usuario que este usuario no likeo.
    matches_db = new JsonArrayDb("matches"); // Guarda todos los matches de cada usuario.
    limit_db = new RocksDb("limit"); //
}

bool Matcher::usersMatch(std::string userId, std::string otherUserId) const {
    return matches_db->has_value(userId, otherUserId);
}