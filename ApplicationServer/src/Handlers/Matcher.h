//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "../SharedData.h"
#include "../UserProfile.h"
#include "../DB/JsonArrayDb.h"
#include "../UsersProfiles.h"

//! Handler para todo lo relacionado con likes, matches, etc.

class Matcher {

    JsonArrayDb *likesReceived_db; // Guarda la cantidad de liks que recibió cada usuario.
    JsonArrayDb *likes_db; // Guarda todos los usuarios que likeo cada usuario.
    JsonArrayDb *dislikes_db; // Guarda todos los usuario que este usuario no likeo.
    JsonArrayDb *matches_db; // Guarda todos los matches de cada usuario.
    RocksDb *limit_db; // Guarda la cantidad de candidatos entregados hoy, cuántos quedan, y cuándo se reinicia la cuenta.

    UsersProfiles &usersProfiles;

    int getInterestsInCommon(UserProfile &user1, UserProfile &user2);

    int calculateScore(UserProfile &userA, UserProfile &userB);

    int calculateDistance(UserProfile &userA, UserProfile &userB);

public:

    Matcher(UsersProfiles &users);

    bool getNextCandidate(std::string userId, UserProfile *profile);

    int postDislike(std::string userId, std::string candidateId);

    bool usersMatch(std::string userId, std::string otherUserId) const;

    std::vector<UserProfile> getMatches(std::string email) const;

    std::vector<std::string> getMatches(const std::string &user);

    std::vector<std::string> getLikes(const std::string &user);

    std::vector<std::string> getLikesReceived(const std::string &user);

    std::vector<std::string> getDislikes(const std::string &user);

    std::vector<UserProfile> getMatches(std::string email);

    std::vector<UserProfile> calculateCandidates(std::string userId);

    JsonArrayDb *candidates_db;

    int postLike(string userId, string candidateId);

    void discardCandidates(string userId, map<string, UserProfile> &candidates);
};

#endif //APPSERVER_MATCHER_H
