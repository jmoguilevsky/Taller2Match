//
// Created by chris on 16/04/16.
//

#include "util.h"
#include <iostream>
#include <algorithm>

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

std::string util::JsonToString(const Json::Value &value) {
    Json::FastWriter writer;
    writer.omitEndingLineFeed();
    return writer.write(value);
}

std::string util::mgStrToString(const struct mg_str &str) {
    return std::string(str.p, str.len);
}

