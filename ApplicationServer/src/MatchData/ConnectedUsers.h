//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_CONNECTEDUSERS_H
#define APPSERVER_CONNECTEDUSERS_H


#include <string>
#include <map>
#include "../Exceptions/AuthorizationException.h"
#include "../Mongoose/MgHTTPClient.h"
//! Mantiene un listado de los usuarios que están conectados y los tokens que se les asignaron
class ConnectedUsers {

    std::map<std::string, std::string> token_userId_map;
    std::map<std::string, std::string> userId_token_map;

private:
    //! Genera un nuevo token para el id de usuario recibido.
    std::string newToken(std::string userId);

public:
    //! A partir del token, devuelve el id del usuario correspondiente.
    std::string getUserId(std::string token);
    //! Hace login de un usuario, y devuelve el token asignado al mismo.
    std::string login(std::string userId);
    //! Hace logout de un usuario a partir del token.
    void logout(std::string token);

};


#endif //APPSERVER_CONNECTEDUSERS_H