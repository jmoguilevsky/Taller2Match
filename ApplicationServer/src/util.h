//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_UTILS_H
#define MULTITHREADMULTICONNECTION_UTILS_H

#include "mongoose-master/mongoose.h"
#include "json/json.h"
#include <string>
#include <vector>

//! Utilidades varias

namespace util {

    bool isNumber(std::string str);

    std::string bufToString(struct mg_connection *connection);

    std::vector<std::string> &split(const std::string &s, char delim,
                                    std::vector<std::string> &elems);

    std::vector<std::string> vectorIntersection(std::vector<std::string> &v1,
                                                std::vector<std::string> &v2);

    std::string mgStrToString(const struct mg_str &str);

    tm currentDate();

    std::string dateToString(tm tstruct);

    tm stringToDate(std::string c);

    Json::Value stringToJson(const std::string &str);

    std::string JsonToString(const Json::Value &value);

    int sum(int a, int b);

    void parseAuthorization(const std::string &authHeader, std::string &user, std::string &token);

}
#endif //MULTITHREADMULTICONNECTION_UTILS_H
