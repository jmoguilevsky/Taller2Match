//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_NOTIFICATIONPOOL_H
#define APPSERVER_NOTIFICATIONPOOL_H

#include <vector>
#include <map>
#include "Notification.h"

class NotificationPool {
    std::map<std::string, std::vector<Notification>> pool;
public:
    void add(Notification notification){
        pool[notification.forUser()].push_back(notification);
    }
    void sendAllForUser(std::string user){
        // Para mandar todas las notificaciones cuando un usuario recién se conecta

    }

};


#endif //APPSERVER_NOTIFICATIONPOOL_H
