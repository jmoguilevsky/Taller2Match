//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_AUTHORIZATIONERROR_H
#define APPSERVER_AUTHORIZATIONERROR_H
#include <exception>
#include <string>
#include "Exception.h"

//! Excepción que se lanza cuando un usuario ingresa credenciales incorrectas o quiere acceder a un dato (por ejemplo, un perfil de usuario) para el cual no tiene autorización.
class AuthorizationException: public Exception {
public:
    AuthorizationException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_AUTHORIZATIONERROR_H
