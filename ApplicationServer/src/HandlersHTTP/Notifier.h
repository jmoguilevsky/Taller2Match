//
// Created by chris on 21/05/16.
//

#ifndef APPSERVER_NOTIFIER_H
#define APPSERVER_NOTIFIER_H


#include <vector>
#include "../HTTP/HTTPRequest.h"

class Notifier {
    std::map<std::string, std::vector<HTTPRequest>> notifications;
public:
    void notifyNewMessage(std::string userA, std::string userB, std::string message);

    void notifyNewMatch(std::string userA, std::string userB);
};


#endif //APPSERVER_NOTIFIER_H
