//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_EXCEPTION_H
#define APPSERVER_EXCEPTION_H


#include <exception>
#include <string>

class Exception : public std::exception {
    std::string msg;
public:
    Exception(std::string msg){
        this -> msg = msg;
    }
    const char * what() {
        return msg.c_str();
    }
};


#endif //APPSERVER_EXCEPTION_H
