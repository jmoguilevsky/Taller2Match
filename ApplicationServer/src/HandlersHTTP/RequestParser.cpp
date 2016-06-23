//
// Created by chris on 11/06/16.
//

#include "RequestParser.h"

void ::RequestParser::parseSignUp(HTTPRequest request, std::string *email, std::string *password,
                                  UserProfile *profile, int *distance) {
    Json::Value info = util::stringToJson(request . getBody())["info"];
    *email = info["email"] . asString();
    *password = info["password"] . asString();
    Json::Value user = util::stringToJson(request . getBody());
    *profile = UserProfile(user);
    std::cout << "info: " << util::JsonToString(info) << std::endl;
    if (info . isMember("distance"))*distance = atoi(info["distance"] . asString() . c_str());
}

void ::RequestParser::parseUpdateProfile(HTTPRequest request, std::string *token, UserProfile *profile) {
    RequestParser::parseToken(request, token);
    Json::Value profileJson = util::stringToJson(request . getBody());
    *profile = UserProfile(profileJson);
}

void ::RequestParser::parseUpdatePhoto(HTTPRequest request, std::string *token, std::string *photo) {
    RequestParser::parseToken(request, token);
    *photo = request . getBody();
}

void ::RequestParser::parseToken(HTTPRequest request, std::string *token) {
    *token = request . getHeader("Authorization");
}

void ::RequestParser::parseViewProfile(HTTPRequest request, std::string *token, std::string *userId) {
    RequestParser::parseToken(request, token);
}

void ::RequestParser::parseLogin(HTTPRequest request, std::string *email, std::string *password, std::string *url) {
    Json::Value credentials = util::stringToJson(request . getBody());
    *email = credentials["email"] . asString();
    *password = credentials["password"] . asString();
    *url = credentials["url"] . asString();
}

void ::RequestParser::parsePostReaction(HTTPRequest &request, std::string *token, std::string *candidateId,
                                        std::string *reaction) {
    RequestParser::parseToken(request, token);
    Json::Value canId = util::stringToJson(request . getBody());
    *candidateId = canId["id"] . asString();
    *reaction = canId["reaction"] . asString();
}

void ::RequestParser::parseSendChat(HTTPRequest request, std::string *token, std::string *candId,
                                    std::string *message) {
    RequestParser::parseToken(request, token);
    Json::Value msg = util::stringToJson(request . getBody());
    *candId = msg["id"] . asString();
    *message = msg["message"] . asString();
}

void ::RequestParser::parseGetHistory(HTTPRequest request, std::string *token, std::string *candId) {
    RequestParser::parseToken(request, token);
    Json::Value info = util::stringToJson(request . getBody());
    *candId = info["id"] . asString();
}

void ::RequestParser::parseGetCandidate(HTTPRequest &request, std::string *token) {
    RequestParser::parseToken(request, token);
}

void ::RequestParser::parseLogout(HTTPRequest request, std::string *token) {
    RequestParser::parseToken(request, token);
}

void ::RequestParser::parseGetNew(HTTPRequest request, std::string *token) {
    RequestParser::parseToken(request, token);
}