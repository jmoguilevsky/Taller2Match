//
// Created by chris on 16/04/16.
//

#include "util.h"
#include <iostream>
#include <algorithm>

#define STR_TO_INT(x) atoi(x.c_str())
#define INT_TO_STR(x) std::to_string(x)

std::vector<std::string> &util::split(const std::string &s, char delim,
                                      std::vector<std::string> &elems) {
    // Split para un string por un char. Devuelve un vector con los tokenManager

    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

Json::Value util::stringToJson(const std::string &str) {
    Json::Value value;
    Json::Reader reader;
    reader.parse(str, value);
    return value;
}

void util::parseAuthorization(const std::string &authHeader, std::string &user, std::string &token) {
    Json::Value auth = stringToJson(authHeader);
    user = auth["email"].asString();
    token = auth["token"].asString();
}

std::string util::JsonToString(const Json::Value &value) {
    Json::FastWriter writer;
    writer.omitEndingLineFeed();
    return writer.write(value);
}

std::string util::mgStrToString(const struct mg_str &str) {
    return std::string(str.p, str.len);
}

