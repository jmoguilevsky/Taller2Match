//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_SHAREDDATA1_H
#define APPSERVER_SHAREDDATA1_H


#include "json/json.h"
#include "UserProfile.h"

//! Se puede "simular" la conexión al shared con una clase que implemente estos métodos.

#include <vector>
using namespace std;

class SharedData {

public:
   virtual bool getUsersList(vector<UserProfile>* users) = 0;

    //! Carga el perfil del usuario con id sharedId.
    virtual bool getUserProfile(string sharedId, UserProfile* userProfile) = 0;

    //! Da de alta un nuevo usuario con el perfil, y carga el sharedId con que se creó.
    virtual bool newUser(UserProfile userProfile, string* sharedId) = 0;

    //! Actualiza el perfil del usuario con id sharedId.
    virtual bool updateProfile(string sharedId, UserProfile profile) = 0;
};


#endif //APPSERVER_SHAREDDATA1_H
