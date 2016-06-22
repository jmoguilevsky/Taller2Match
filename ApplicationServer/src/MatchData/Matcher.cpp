//

#include <iostream>
#include <set>
#include <algorithm>
#include <list>
#include "Matcher.h"
#include "../Utilities/Date.h"
#include "../Exceptions/AuthorizationException.h"

#define DAILY_CANDIDATES 10

void Matcher::postReaction(std::string userId, std::string candidateId, std::string reaction) {
    bool ok = candidates_db->has_value(userId, candidateId);

    if (!ok) throw AuthorizationException("Candidate is not a suggested candidate!");
    
    candidates_db->remove_value(userId, candidateId);

    if(reaction == "LIKE") {

        likes_db -> append_value(userId, candidateId);

        likesReceived_db -> append_value(candidateId, userId);

        if (likes_db -> has_value(candidateId, userId)) {
            // Hay match
            matches_db -> append_value(userId, candidateId);
            matches_db -> append_value(candidateId, userId);
            std::cout << "MATCH BETWEEN USERS " + userId + " AND " + candidateId << std::endl;
        }
    } else if(reaction == "DISLIKE") {

        dislikes_db -> append_value(userId, candidateId);

    } else throw Exception("Invalid reaction");

}

std::vector<std::string> Matcher::getLikesReceived(const std::string &userId) {
    std::string list;
    return likesReceived_db->values(userId);
}

std::vector<std::string> Matcher::getLikes(const std::string &userId) {
    return likes_db->values(userId);
}

std::vector<std::string> Matcher::getMatches(std::string userId) {
    return matches_db->values(userId);
}

std::vector<std::string> Matcher::getDislikes(const std::string &user) {
    // Devuelve los users que user rechazó.
    /*return util::valuesAsVector(noMatches, user);*/
    return std::vector<std::string>();
}

int Matcher::candidatesLeft(std::string userId){

}

UserProfile Matcher::getNextCandidate(std::string userId) {

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
        std::vector<std::string> newCandidates = calculateCandidates(userId);
        if(newCandidates.size() != 0) {
            for (int i = 0; i < newCandidates.size(); i++) {
                candidates_db->append_value(userId, newCandidates[i]);
            }
            limit_db->save(userId, today.str());
        }
    }
    // Si es el mismo día, mando el siguiente candidato, entre los no likeados.

    std::vector<std::string> candidates = candidates_db->values(userId);
    UserProfile profile;
    if (candidates.size() != 0) {
        std::string nextId = candidates[0];
        profile = usersProfiles.getProfile(nextId);
    }

    return profile;
}

double Matcher::calculateDistance(UserProfile &userA, UserProfile &userB) {
    // Calcula la distancia entre los dos usuarios.
    double latA = userA.getLatitude();
    double lonA = userA.getLongitude();
    double latB = userB.getLatitude();
    double lonB = userB.getLongitude();
    return util::distanceEarth(latA, lonA, latB, lonB);
}

int Matcher::calculateScore(UserProfile &userId, UserProfile &otherUserId) {
    // Calcula el "score" que tiene el match userA - userB, según sus intereses y distancia.
    int intInCommon = getInterestsInCommon(userId, otherUserId);
    double distance = calculateDistance(userId, otherUserId);
    //if (distance > MAX_DISTANCE)
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

std::vector<std::string> Matcher::calculateCandidates(std::string userId) {

    std::map<std::string, UserProfile> candidates = usersProfiles.getUsers();
    UserProfile userProfile = candidates[userId];
    candidates.erase(userId);

    filterBySex(candidates, userProfile.getSexInterest(), userProfile.getSex());

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

    // Los ordeno por puntaje

    std::vector<std::pair<std::string, int>> orderedByScore = sortDescByValue(scores);

    // Agarrar los DAILY_LIMIT con más puntaje

    std::vector<std::string> newCandidates;
    int nCand = (int) (candidates.size() < DAILY_CANDIDATES ? candidates.size() : DAILY_CANDIDATES);
    for (int i = 0; i < nCand; i++) {
        std::string candidateId = orderedByScore[i].first;
        newCandidates.push_back(candidateId);
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

Matcher::Matcher(ProfilesDatabase &users) : usersProfiles(users) {
    candidates_db = new JsonArrayDb("db/candidates");
    likesReceived_db = new JsonArrayDb("db/likesReceived"); // Guarda la cantidad de liks que recibió cada usuario.
    likes_db = new JsonArrayDb("db/likes"); // Guarda todos los usuarios que likeo cada usuario.
    dislikes_db = new JsonArrayDb("db/dislikes"); // Guarda todos los usuario que este usuario no likeo.
    matches_db = new JsonArrayDb("db/matches"); // Guarda todos los matches de cada usuario.
    limit_db = new RocksDb("db/limit"); //
}

std::vector<Interest> Matcher::getAllInterests(){
    return usersProfiles.getAllInterests();
}

bool Matcher::usersMatch(std::string userId, std::string otherUserId) const {
    return matches_db->has_value(userId, otherUserId);
}

void Matcher::filterBySex(map<string, UserProfile> &candidates, string is, string wants) {
    std::vector<std::string> toRemove;
    for (std::map<std::string, UserProfile>::iterator it = candidates.begin();
         it != candidates.end(); ++it) {
        UserProfile candidateProfile = it->second;
        std::string candidateIs = candidateProfile.getSex();
        std::string candidateWants = candidateProfile.getSexInterest();
        if(candidateIs != is && candidateWants != wants){
            toRemove.push_back(it -> first);
        }
    }

    for (int i  = 0; i < toRemove.size(); i++){
        candidates.erase(toRemove[i]);
    }
}
