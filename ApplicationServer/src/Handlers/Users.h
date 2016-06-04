//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGIN_H
#define APPSERVER_LOGIN_H

#include "../SharedData.h"
#include "../DB/KeyValueDb.h"
#include "../DB/RocksDb.h"
#include "../UsersProfiles.h"

//! Handler para la cosas relacionadas con el login, alta y baja de usuarios, etc.
// también mantiene los tokens, y qué usuarios están o no conectados.

class Users {
    std::map<std::string, std::string> userId_url;
    std::map<std::string, std::string> token_userId_map;
    std::map<std::string, bool> userId_connected_map; // Si está conectado, tiene como valor el token. Si no está conectado, el usuario no está en esta tabla.
    UsersProfiles &userProfiles;
    RocksDb *email_pwd_db;

    void invalidateToken(std::string token);

    std::string newToken(std::string appId);

public:
    //! Recibe un UsersProfiles, que usará para obtener los perfiles de los usuarios, crear nuevos, y modificarlos o eliminarlos.
    Users(UsersProfiles &users);
    //! Signup de un usuario, dado su mail y password, y el perfil. Devuelve False si hubo algún problema (por ejemplo, porque ya hay un usuario con ese mail), o True en otro caso.
    bool signUp(std::string email, std::string password, UserProfile userProfile);
    //! Actualiza el perfil del usuario con id userId, con el nuevo perfil recibido.
    bool updateProfile(std::string userId, UserProfile newProfile);
    //! Actualiza la foto de perfil del usuario con la nueva foto recibida.
    bool updatePhoto(std::string userId, Json::Value newPhoto);
    //! Login del usuario, dado su mail y password. Carga el perfil y el token si se pudo loguear, y devuelve True en ese caso. False si hubo algún error.
    bool login(std::string email, std::string password, std::string *token, UserProfile *profile, std::string url);

    //! Logout del usuario dado su token. Requiere que se verifique previamente que el token es válido.
    void logout(std::string token);
    //! TODO sacar esta función
    bool userExists(std::string userId) {
        return true;
    }
    //! Devuelve True si el usuario está conectado actualmente, False si no.
    bool isConnected(std::string email) ;
    //! Carga el perfil del usuario con id userId en prof. Si hubo algún problema devuelve False, True en otro caso.
    bool getUserProfile(std::string userId, UserProfile* prof) ;
    //! Carga el userId, dado el token del usuario. Devuelve false si el token es inválido.
    bool getUserId(string token, string *userId);

    string getUserURL(string userId);
};

#endif //APPSERVER_LOGIN_H
