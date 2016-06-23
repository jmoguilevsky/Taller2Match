//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_PARSEEXCEPTION_H
#define APPSERVER_PARSEEXCEPTION_H


#include "Exception.h"
//! Excepción  que se lanza cuando hay algún error en el parseo de un request (por ejemplo, un Json mal formateado, con una '}' faltante)
class ParseException: public Exception{
public:
    ParseException(std::string msg):Exception(msg){}
};


#endif //APPSERVER_PARSEEXCEPTION_H
