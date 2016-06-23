//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_SHAREDDATA1_H
#define APPSERVER_SHAREDDATA1_H


#include "../json/json.h"
#include "../Profile/UserProfile.h"


#include <vector>
using namespace std;

//! Se puede "simular" la conexión al shared con una clase que implemente estos métodos.
class SharedProfilesDatabase {

public:

    //! Devuelve un vector con todos los perfiles de todos los usuarios registrados en el shared.
    virtual std::vector<UserProfile> getUsersList() = 0;

    //! Carga el perfil del usuario con id sharedId.
    virtual UserProfile getUserProfile(std::string sharedId) = 0;

    //! Da de alta un nuevo usuario con el perfil, y carga el sharedId con que se creó.
    virtual std::string newUser(UserProfile userProfile) = 0;

    //! Actualiza el perfil del usuario con id sharedId.
    virtual void updateProfile(string sharedId, UserProfile profile) = 0;

    //! Devuelve una lista de todos los intereses que ya existen
    virtual std::vector<Interest> getAllInterests() = 0;
};


#endif //APPSERVER_SHAREDDATA1_H
