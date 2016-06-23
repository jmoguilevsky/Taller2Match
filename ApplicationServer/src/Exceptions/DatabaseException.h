//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_DATABASEEXCEPTION_H
#define APPSERVER_DATABASEEXCEPTION_H
#include "Exception.h"

//! Excepción que se lanza cuando hay algún error en algunba base de datos.
class DatabaseException : public Exception {
public:
    DatabaseException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_DATABASEEXCEPTION_H
