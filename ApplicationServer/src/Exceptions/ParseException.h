//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_PARSEEXCEPTION_H
#define APPSERVER_PARSEEXCEPTION_H


#include "Exception.h"

class ParseException: public Exception{
public:
    ParseException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_PARSEEXCEPTION_H
