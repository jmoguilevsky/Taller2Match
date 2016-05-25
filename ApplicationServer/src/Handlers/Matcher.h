//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "../SharedData.h"
#include "../UserProfile.h"
#include "../DB/RocksDB.h"
#include "../UsersProfiles.h"

//! Handler para todo lo relacionado con likes, matches, etc.

class Matcher {

    RocksDB* likesReceived_db; // Guarda la cantidad de liks que recibió cada usuario.
    RocksDB* likes_db; // Guarda todos los usuarios que likeo cada usuario.
    RocksDB* dislikes_db; // Guarda todos los usuario que este usuario no likeo.
    RocksDB* matches_db; // Guarda todos los matches de cada usuario.
    RocksDB* limit_db; // Guarda la cantidad de candidatos entregados hoy, cuántos quedan, y cuándo se reinicia la cuenta.

    UsersProfiles &usersProfiles;

    int getInterestsInCommon(UserProfile &user1, UserProfile &user2);

    int calculateScore(UserProfile &userA, UserProfile &userB);

    int calculateDistance(UserProfile &userA, UserProfile &userB);

public:

    Matcher(UsersProfiles &users) : usersProfiles(users) {
            candidates_db = new RocksDB("candidates");
        likesReceived_db = new RocksDB("likesReceived"); // Guarda la cantidad de liks que recibió cada usuario.
        likes_db = new RocksDB("likes"); // Guarda todos los usuarios que likeo cada usuario.
        dislikes_db =  new RocksDB("dislikes"); // Guarda todos los usuario que este usuario no likeo.
        matches_db = new RocksDB("matches"); // Guarda todos los matches de cada usuario.
        limit_db = new RocksDB("limit"); //
    }

    bool getNextCandidate(std::string userId, UserProfile *profile);

    int postDislike(std::string userId, std::string candidateId);

    bool usersMatch(std::string userId, std::string otherUserId) const;

    std::vector<UserProfile> getMatches(std::string email) const;

    std::string getMatches(const std::string &user);

    std::string getLikes(const std::string &user);

    int getLikesReceived(const std::string &user);

    std::vector<std::string> getDislikes(const std::string &user);

    std::vector<UserProfile> getMatches(std::string email);

    std::vector<UserProfile> calculateCandidates(std::string userId);

    std::vector<UserProfile> candidatesLeft(std::string userId);

    RocksDB* candidates_db;

    int postLike(string userId, string candidateId);
};

#endif //APPSERVER_MATCHER_H
