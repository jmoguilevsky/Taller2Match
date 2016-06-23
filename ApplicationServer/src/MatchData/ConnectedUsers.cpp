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

std::string ConnectedUsers::login(std::string userId) {
    // Create new token
    if (userId_token_map . count(userId) == 1) throw Exception("User already logged in");
    std::string token = newToken(userId);
    token_userId_map[token] = userId;
    userId_token_map[userId] = token;
    Log::info("USER" + userId + " LOGGED IN");
    std::cout << "USER " << userId << " LOGGED IN" << std::endl;
    return token;
}

std::string ConnectedUsers::getUserId(std::string token) {
    if (token_userId_map . count(token) == 0) throw AuthorizationException("Invalid token");
    return token_userId_map[token];
}

std::string ConnectedUsers::newToken(std::string userId) {
    return userId;
}