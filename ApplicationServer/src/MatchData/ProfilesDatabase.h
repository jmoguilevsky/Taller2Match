//
// Created by chris on 23/05/16.
//

#ifndef APPSERVER_USERSPROFILES_H
#define APPSERVER_USERSPROFILES_H

#include <string>
#include "../json/json.h"
#include "../Profile/UserProfile.h"
#include "SharedProfilesDatabase.h"
#include "../DB/RocksDb.h"

using namespace std;

//! Información relacionada a los perfiles de los usuarios registrados en este app server.
//! Es decir, sirve como un "filtro" para los usuarios que devuelve SharedProfilesDatabase. Mantiene los ids internos al app server, y
//! "sabe" a que sharedId y email corresponde cada userId interno.

class ProfilesDatabase {
private:
    RocksDb *email_pwd_map;
    RocksDb *userId_email_map;
    RocksDb *email_userId_map;
    RocksDb *email_sharedId_map;
    RocksDb *distance_db;
    int n;

    string getNextId();

    SharedProfilesDatabase* sharedData;

public:
    ProfilesDatabase();

    //! Setea el SharedProfilesDatabase donde estarán almacenados los perfiles de los usuarios.
    void setShared(SharedProfilesDatabase &sharedData);
    //! A partir de un email, devuelve el id interno de ese usuario.
    string getUserId(string email);
    //! A partir del id interno, carga el perfil del usuario. Si no hay nadie con ese id, no carga nada y devuelve False.
    UserProfile getProfile(string userId);
    //! Registra un nuevo usuario con el perfil recibido, y carga el id interno creado para él en userId.
    void newUser(std::string email, std::string password, UserProfile userProfile, int maxDistance);
    //! Carga un map con clave = id *interno* del usuario, valor = perfil del usuario
    map<string, UserProfile> getUsers();
    //! Dado el id interno del usuario, actualiza su perfil con el recibido.
    void updateProfile(string userId, UserProfile userProfile);

    //!
    int getMaxDistance(string userId);


    bool verify(string email, string password);

    vector<Interest> getAllInterests();
};


#endif //APPSERVER_USERSPROFILES_H
