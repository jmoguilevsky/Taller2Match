//
// Created by chris on 26/03/16.
//

#ifndef JSONTEST_USER_H
#define JSONTEST_USER_H

#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include "../json/json.h"
#include "Interest.h"

typedef std::set<Interest> InterestList;

//! Representa el perfil de un usuario y métodos para consulta de distintos campos del mismo.
class UserProfile {
    std::string name;
    std::string id;
    InterestList interestList;

public:
    //! Devuelve un listado de todos los intereses del usuario.
    const InterestList &getInterests();

    //! Crea un perfil de usuario con los datos vacíos.
    UserProfile();

    //! Crea un perfil de usuario a partir de un objeto Json.
    UserProfile(Json::Value &user);

    //! Devuelve el id del usuario.
    std::string getId() const;

    //! Devuelve la latitud de la última ubicación conocida del usuario.
    double getLatitude() const;
    //! Devuelve la longitud de la última ubicación conocida del usuario.
    double getLongitude() const;

    std::string getSexInterest();

    //! Devuelve el email con el que se registró el usuario.
    std::string getEmail() const;

    //! Devuelve el perfil del usuario como un Json::Value.
    Json::Value getJson() const;

    //! Cambia el Id del perfil, esto se usa para pasar entre el Id interno del app server y el id del shared server.
    void changeId(std::string userId);

    //! Carga el perfil con los datos un string que contiene el perfil en formato Json.
    void fromJson(std::string user);

    std::string getSex();

private:

    double latitude;
    double longitude;

    void parseInterests(Json::Value &user);

    std::string email;

    Json::Value user;
    std::string sexInterest;
    std::string sex;
};

#endif //JSONTEST_USER_H
