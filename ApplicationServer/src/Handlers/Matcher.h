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
    //! Guarda la cantidad de likes que recibió cada usuario.
    JsonArrayDb *likesReceived_db;
    //! Guarda todos los usuarios que likeo cada usuario.
    JsonArrayDb *likes_db;
    //! Guarda todos los usuario que este usuario no likeo.
    JsonArrayDb *dislikes_db;
    //! Guarda todos los matches de cada usuario.
    JsonArrayDb *matches_db;
    //! Guarda la cantidad de candidatos entregados hoy, cuántos quedan, y cuándo se reinicia la cuenta.
    RocksDb *limit_db;
    //! Guarda los candidatos que fueron calculados para cada usuario.
    JsonArrayDb *candidates_db;

    UsersProfiles &usersProfiles;

    //! Devuelve la cantidad de intereses en común entre los dos perfiles de usuario.
    int getInterestsInCommon(UserProfile &user1, UserProfile &user2);

    //! Devuelve el "puntaje" (i.e. "compatibilidad") entre los dos usuarios.
    int calculateScore(UserProfile &userA, UserProfile &userB);

    //! Calcula la distancia entre los dos usuarios.
    int calculateDistance(UserProfile &userA, UserProfile &userB);

public:
    //! Recibe un UsersProfiles, que utilizará para obtener la información de los perfiles de los usuarios.
    Matcher(UsersProfiles &users);
    //! Carga en _profile_ el perfil del próximo candidato para el usuario con id userId. Devuelve true si no hay problema.Si no hay candidatos o hay un error, devuelve False y no modifica _profile_.
    bool getNextCandidate(std::string userId, UserProfile *profile);

    //! Guarda el candidato en la lista de rechazados del usuario.
    int postDislike(std::string userId, std::string candidateId);
    //! Devuelve True si hay un match enntre los usuarios, False si no.
    bool usersMatch(std::string userId, std::string otherUserId) const;

    //! Devuelve todos los matches del usuario.
    std::vector<std::string> getMatches(const std::string &user);

    //! Devuelve todos los likes del usuario.
    std::vector<std::string> getLikes(const std::string &user);

    //! Devuelve todos los usuarios que le dieron like a este usuario.
    std::vector<std::string> getLikesReceived(const std::string &user);

    //! Devuelve todos los usuarios que el usuario rechazó.
    std::vector<std::string> getDislikes(const std::string &user);

    //! Devuelve los perfiles de todos los matches del usuario.
    std::vector<UserProfile> getMatches(std::string email);

    //! Calcula una nuevba tanda de candidatos para el usuario.
    std::vector<UserProfile> calculateCandidates(std::string userId);

    //! Guarda un like del usuario al candidate.
    int postLike(string userId, string candidateId);

    //! En la lista preliminar de candidatos, descarta los ya han sugeridos previamente.
    void discardCandidates(string userId, map<string, UserProfile> &candidates);
};

#endif //APPSERVER_MATCHER_H
