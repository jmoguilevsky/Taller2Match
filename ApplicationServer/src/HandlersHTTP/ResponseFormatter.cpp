//
// Created by chris on 11/06/16.
//

#include "ResponseFormatter.h"
// URI: /users/*

HTTPResponse ResponseFormatter::formatLogin(std::string token, UserProfile profile) {
    Json::Value profJson = profile.getJson();
    profJson["token"] = token;
    return HTTP::OK(profJson);
}

HTTPResponse ResponseFormatter::formatViewProfile(UserProfile profile) {
    return HTTP::OK(profile.getJson());
}

HTTPResponse ResponseFormatter::formatGetHistory(std::string history) {
    return HTTP::OK(history);
}

HTTPResponse ResponseFormatter::formatGetMatches(std::string status) {
    // TODO
    return HTTP::OK();
}

HTTPResponse ResponseFormatter::formatGetCandidate(UserProfile profile) {
    return HTTP::OK(profile.getJson());
}

HTTPResponse ResponseFormatter::formatPostReaction(std::string status){

}