//

#include <iostream>
#include <set>
#include <algorithm>
#include <list>
#include "Matcher.h"
#include "../Date.h"

#define DAILY_CANDIDATES 10

int Matcher::postLike(std::string userId, std::string candidateId) {
    std::string candidates;
    candidates_db -> get (userId, candidates);

    Json::Value array = util::stringToJson(candidates);

    // ***** Verifico que sea un candidato sugerido ( o que sea el PRIMERO DE LA LISTA?)

    bool ok = false;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].asString() == candidateId) ok = true;
    }
    if (!ok) {
        return 0;
        // NO ES UN CANDIDATE -> ERROR
    }

    // *****
    // ***** Genero el nuevo listado de candidatos, o sea: saco este candidato de la lista
    Json::Value newArray;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].asString() != candidateId) newArray.append(array[i]);
    }
    // *****

    candidates_db->save(userId, util::JsonToString(newArray));

    append(*likes_db, userId, candidateId);
    std::cout << "LIKES: " << std::endl;
    likes_db->listAll();

    Json::Value thisUserId = userId;
    Json::Value lastId = candidateId;

    append(*likesReceived_db, candidateId, thisUserId);
    std::cout << "LIKES RECEIVED: " << std::endl;
    likesReceived_db->listAll();

    if (valueExists(*likes_db, candidateId, userId)) {
        append(*matches_db, userId, lastId);
        append(*matches_db, candidateId, thisUserId);
    }

    std::cout << "MATCHESSS: " << std::endl;
    matches_db->listAll();

    return 0;
}

int Matcher::postDislike(std::string userId, std::string candidateId) {
    std::string candidates;
    candidates_db -> get (userId, candidates);

    Json::Value array = util::stringToJson(candidates);

    // ***** Verifico que sea un candidato sugerido ( o que sea el PRIMERO DE LA LISTA?)

    bool ok = false;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].asString() == candidateId) ok = true;
    }
    if (!ok) {
        return 0;
        // NO ES UN CANDIDATE -> ERROR
    }

    // *****
    // ***** Genero el nuevo listado de candidatos, o sea: saco este candidato de la lista
    Json::Value newArray;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].asString() != candidateId) newArray.append(array[i]);
    }
    // *****

    candidates_db->save(userId, util::JsonToString(newArray));

    append(*dislikes_db, userId, candidateId);
    std::cout << "DISLIKES: " << std::endl;
    dislikes_db->listAll();
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

bool Matcher::getNextCandidate(std::string userId, UserProfile *profile) {

    std::string lastTimeStr;

    //limit_db->listAll();

    limit_db->get(userId, lastTimeStr);

    //candidates_db ->listAll();

    Date lastTime;

    candidates_db->listAll();

    if (lastTimeStr != "") {
        lastTime = Date(lastTimeStr);
    }
    Date today = Date::today();

    if (lastTime < today) {
        // Pasó más de un día desde la última vez que se buscaron los candidatos
        // Busco candidatos otra vez
        std::vector<UserProfile> newCandidates = calculateCandidates(userId);
        Json::Value array;
        for (int i = 0; i < newCandidates.size(); i++) {
            Json::Value id = newCandidates[i].getId();
            array.append(id);
        }
        limit_db->save(userId, today.str());
        candidates_db->save(userId, util::JsonToString(array));
    }
    // Si es el mismo día, mando el siguiente candidato, entre los no likeados.
    std::string candidates;
    candidates_db->get(userId, candidates);
    Json::Value array = util::stringToJson(candidates);
    if (array.size() == 0) return false;
    std::string nextId = array[0].asString();


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


std::vector<UserProfile> Matcher::calculateCandidates(std::string userId) {

    std::vector<UserProfile> candidates;
    usersProfiles.getUsers(&candidates);
    UserProfile userProfile;

    // ***** Saco el perfil de ESTE usuario de la lista

    for (std::vector<UserProfile>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
        if (it->getId() == userId) {
            userProfile = *it;
            candidates.erase(it);
            break;
        }
    }

    // *****

    // ***** Cargo el mapa userId -> perfil

    std::map<std::string, UserProfile> candidatesWithId;

    for (int i = 0; i < candidates.size(); i++) {
        candidatesWithId[candidates[i].getId()] = candidates[i];
    }

    // *****

    // ***** Descarto los candidatos que ya estan en likes, dislikes, o matches

    std::string likes;
    likes_db->get(userId, likes);
    Json::Value arrayLikes = util::stringToJson(likes);
    for (int i = 0; i < arrayLikes.size(); i++) {
        if (candidatesWithId.count(arrayLikes[i].asString()) == 1) candidatesWithId.erase(arrayLikes[i].asString());
    }


    std::string dislikes;
    dislikes_db->get(userId, dislikes);
    Json::Value arrayDislikes = util::stringToJson(dislikes);
    for (int i = 0; i < arrayDislikes.size(); i++) {
        if (candidatesWithId.count(arrayDislikes[i].asString()) == 1)
            candidatesWithId.erase(arrayDislikes[i].asString());
    }


    std::string matches;
    matches_db->get(userId, matches);
    Json::Value arrayMatches = util::stringToJson(matches);
    for (int i = 0; i < arrayMatches.size(); i++) {
        if (candidatesWithId.count(arrayMatches[i].asString()) == 1) candidatesWithId.erase(arrayMatches[i].asString());
    }

    // *****

    // ***** Calculo el "puntaje" para cada usuario

    std::map<std::string, int> scores;

    for (std::map<std::string, UserProfile>::iterator it = candidatesWithId.begin();
         it != candidatesWithId.end(); ++it) {
        UserProfile otherUserProfile = it->second;
        std::string otherUserId = otherUserProfile.getId();
        scores[otherUserId] = calculateScore(userProfile, otherUserProfile);
    }

    // TODO ordenarlos por score y devolver DAILY_CANDIDATES

    std::vector<std::pair<std::string, int>> orderedByScore = sortDescByValue(scores);

    // Agarrar los DAILY_LIMIT con más puntaje

    std::vector<UserProfile> score;
    int nCand;
    if (DAILY_CANDIDATES < candidatesWithId.size())nCand = DAILY_CANDIDATES;
    else nCand = candidatesWithId.size();
    for (int i = 0; i < nCand; i++) {
        std::string userId = orderedByScore[i].first;
        UserProfile userPr = candidatesWithId[userId];
        score.push_back(userPr);
    }
    return score;
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