//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_SHAREDSERVEREXCEPTION_H
#define APPSERVER_SHAREDSERVEREXCEPTION_H


#include "Exception.h"

//!Excepción que se lanza cuando no se puede cumplir con un pedido hacia el shared server, por ejemplo, porque no está disponible actualmente.
class SharedServerException: public Exception {
public:
    SharedServerException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_SHAREDSERVEREXCEPTION_H
