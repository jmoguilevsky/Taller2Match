//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_UTILS_H
#define MULTITHREADMULTICONNECTION_UTILS_H

#include "../Mongoose/mongoose-master/mongoose.h"
#include "../json/json.h"
#include <string>
#include <vector>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0
//! Utilidades varias

namespace util {

    std::vector<std::string> &split(const std::string &s, char delim,
                                    std::vector<std::string> &elems);

    std::vector<std::string> vectorIntersection(std::vector<std::string> &v1,
                                                std::vector<std::string> &v2);
    std::string mgStrToString(const struct mg_str &str);

    Json::Value stringToJson(const std::string &str);

    std::string JsonToString(const Json::Value &value);


    double deg2rad(double deg);

    double rad2deg(double rad);

    double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

}
#endif //MULTITHREADMULTICONNECTION_UTILS_H
