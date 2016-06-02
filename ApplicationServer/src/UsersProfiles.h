//
// Created by chris on 23/05/16.
//

#ifndef APPSERVER_USERSPROFILES_H
#define APPSERVER_USERSPROFILES_H

#include <string>
#include "json/json.h"
#include "UserProfile.h"
#include "SharedData.h"
#include "DB/RocksDb.h"

using namespace std;

//! Información relacionada a los perfiles de los usuarios registrados en este app server.
//! Es decir, sirve como un "filtro" para los usuarios que devuelve SharedData. Mantiene los ids internos al app server, y
//! "sabe" a que sharedId y email corresponde cada userId interno.

class UsersProfiles {
private:

    RocksDb *userId_email_map;
    RocksDb *email_userId_map;
    RocksDb *email_sharedId_map;

    int n;

    string getNextId();

    SharedData* sharedData;

public:
    UsersProfiles();

    //! Setea el SharedData donde estarán almacenados los perfiles de los usuarios.
    void setShared(SharedData &sharedData);

    //! A partir de un email, devuelve el id interno de ese usuario.
    string getUserId(string email);
    //! A partir del id interno, carga el perfil del usuario. Si no hay nadie con ese id, no carga nada y devuelve False.
    bool getProfile(string userId, UserProfile *userProfile);
    //! Registra un nuevo usuario con el perfil recibido, y carga el id interno creado para él en userId.
    bool newUser(UserProfile userProfile, string *userId);
    //! Carga un map con clave = id *interno* del usuario, valor = perfil del usuario
    bool getUsers(map<string, UserProfile> *users);
    //! Dado el id interno del usuario, actualiza su perfil con el recibido.
    bool updateProfile(string userId, UserProfile userProfile);
};


#endif //APPSERVER_USERSPROFILES_H
