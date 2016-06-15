//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_CONNECTEDUSERS_H
#define APPSERVER_CONNECTEDUSERS_H


#include <string>
#include <map>
#include "../Exceptions/AuthorizationException.h"
#include "../Mongoose/MgHTTPClient.h"

class ConnectedUsers {

    std::map<std::string, std::string> token_userId_map;
    std::map<std::string, std::string> userId_token_map;
    std::map<std::string, std::string> userId_url_map;

private:

    std::string newToken(std::string userId);

public:

    std::string getUserUrl(std::string userId);

    std::string getUserId(std::string token);

    std::vector<std::string> getAllUsers();

    std::string login(std::string userId, std::string url);

    bool isConnected(std::string userId);

    void disconnect(std::string userId);

    void logout(std::string token);

};


#endif //APPSERVER_CONNECTEDUSERS_H