//
// Created by chris on 11/06/16.
//

#include <iostream>
#include "ConnectedUsers.h"
#include "../Log/Log.h"

void ConnectedUsers::logout(std::string token) {
    if (token_userId_map . count(token) == 0) throw AuthorizationException("Invalid token");
    std::string userId = token_userId_map[token];
    userId_token_map . erase(userId);
    token_userId_map . erase(token);
    Log::info("USER" + userId + " LOGGED OUT");
    std::cout << "USER " << userId << " LOGGED OUT" << std::endl;
}

void ConnectedUsers::disconnect(std::string userId) {
    std::string token = userId_token_map[userId];
    userId_token_map . erase(userId);
    token_userId_map . erase(token);
    userId_url_map . erase(userId);
    Log::info("USER" + userId + " DISCONNECTED");
    std::cout << "USER " << userId << " DISCONNECTED" << std::endl;
}

bool ConnectedUsers::isConnected(std::string userId) {
    return userId_token_map . count(userId) == 1;
}

std::string ConnectedUsers::login(std::string userId, std::string url) {
    // Create new token
    if (userId_token_map . count(userId) == 1) throw Exception("User already logged in");
    std::string token = newToken(userId);
    token_userId_map[token] = userId;
    userId_token_map[userId] = token;
    userId_url_map[userId] = url;
    Log::info("USER" + userId + " LOGGED IN");
    std::cout << "USER " << userId << " LOGGED IN" << std::endl;
    return token;
}

std::vector<std::string> ConnectedUsers::getAllUsers() {
    std::vector<std::string> users;
    for (std::map<std::string, std::string>::iterator it = userId_url_map . begin();
         it != userId_url_map . end(); ++it) {
        users . push_back(it -> first);
    }
    return users;
}

std::string ConnectedUsers::getUserId(std::string token) {
    if (token_userId_map . count(token) == 0) throw AuthorizationException("Invalid token");
    return token_userId_map[token];
}

std::string ConnectedUsers::getUserUrl(std::string userId) {
    return userId_url_map[userId];
}

std::string ConnectedUsers::newToken(std::string userId) {
    return userId;
}