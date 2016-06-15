//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_DATABASEEXCEPTION_H
#define APPSERVER_DATABASEEXCEPTION_H
#include "Exception.h"

class DatabaseException : public Exception {
public:
    DatabaseException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_DATABASEEXCEPTION_H
