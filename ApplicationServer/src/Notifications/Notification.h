//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_NOTIFICATION_H
#define APPSERVER_NOTIFICATION_H


#include <string>

class Notification {
    std::string user;
public:
    std::string serialize(){
        return user;
    };
    std::string forUser(){
        return user;
    }
};


#endif //APPSERVER_NOTIFICATION_H
