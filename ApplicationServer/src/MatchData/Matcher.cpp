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
    std::string suggested;
    candidate_db -> get(userId, suggested);

    // Si no es el último candidato sugerido => ERROR!

    if (candidateId != suggested) throw AuthorizationException("Candidate is not a suggested candidate!");

    std::string limitStr;
    limit_db -> get(userId, limitStr);
    Json::Value limitJson = util::stringToJson(limitStr);
    limitJson["left"] = limitJson["left"] . asInt() - 1;

    limit_db -> save(userId, util::JsonToString(limitJson));

    candidate_db -> save(userId, ""); // Equivalente a borrar la clave

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

std::vector<UserProfile> Matcher::getMatches(std::string userId) {
    std::vector<std::string> matches = matches_db->values(userId);
    std::vector<UserProfile> profiles;
    for(int i = 0; i < matches.size(); i++){
        std::cout << "match id: " << matches[i] << std::endl;
        std::cout << "profile: " << util::JsonToString((usersProfiles.getProfile(matches[i])).getJson()) << std::endl;
        profiles.push_back(usersProfiles.getProfile(matches[i]));
    }
    return profiles;
}

UserProfile Matcher::getNextCandidate(std::string userId) {

    std::string limitStr;

    limit_db->get(userId, limitStr);

    Json::Value limitJson = util::stringToJson(limitStr);
    std::string lastTimeStr = limitJson["lastTime"].asString();

    Date lastTime;

    if (lastTimeStr != "") {
        lastTime = Date(lastTimeStr);
    }

    Date today = Date::today();

    if (lastTime < today) {
        limitJson["lastTime"] = today . str();
        limitJson["left"] = DAILY_CANDIDATES;
    }

    UserProfile nextCandidate;

    if (limitJson["left"] . asInt() > 0) {
        // Cada vez que me pide un candidato, pido todos los usuarios y hago todo el cálculo otra vez!
        nextCandidate = calculateNextCandidate(userId);
        candidate_db -> save(userId, nextCandidate . getId()); // Tiene el último candidato sugerido
        limit_db -> save(userId, util::JsonToString(limitJson));
    } else if (limitJson["left"] . asInt() == 0) {
        throw Exception("No more candidates today!");
    }

    return nextCandidate;
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

UserProfile Matcher::calculateNextCandidate(std::string userId) {

    std::map<std::string, UserProfile> candidates = usersProfiles.getUsers();
    std::cout << candidates . size() << " candidates initially" << std::endl;

    UserProfile userProfile = candidates[userId];
    candidates.erase(userId);

    std::cout << candidates . size() << " candidates remaining before filtering by sex interests" << std::endl;

    filterBySex(candidates, userProfile.getSexInterest(), userProfile.getSex());

    std::cout << candidates . size() << " candidates remaining after filtering by sex interests" << std::endl;

    // ***** Descarto los candidatos que ya estan en likes y dislikes


    std::cout << candidates . size() << " candidates remaining before discarding" << std::endl;

    discardCandidates(userId, candidates);
    std::cout << candidates . size() << " candidates remaining after discarding" << std::endl;

    //filterByDistance(candidates,userProfile.getLatitude(), userProfile.getLongitude(), usersProfiles.getMaxDistance(userId));

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

    // Agarro el mejor candidato

    if (candidates . size() == 0) throw Exception("Couldn't find more candidates!");

    return candidates[orderedByScore[0] . first];

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
    candidate_db = new RocksDb("db/candidate");
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

void Matcher::filterByDistance(map<string, UserProfile> &candidates, double lat, double lon, int distance) {
    std::vector<std::string> toRemove;
    for (std::map<std::string, UserProfile>::iterator it = candidates . begin();
         it != candidates . end(); ++it) {
        UserProfile candidateProfile = it -> second;
        double candLon = candidateProfile . getLongitude();
        double candLat = candidateProfile . getLatitude();
        if (util::distanceEarth(lat, lon, candLon, candLat) > (double) distance) {
            toRemove . push_back(it -> first);
        }
    }

    for (int i = 0; i < toRemove . size(); i++) {
        candidates . erase(toRemove[i]);
    }
}