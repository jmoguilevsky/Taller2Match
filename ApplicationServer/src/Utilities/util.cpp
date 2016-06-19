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

double ::util::deg2rad(double deg) {
    return (deg * pi / 180);
}

double ::util::rad2deg(double rad) {
    return (rad * 180 / pi);
}

double ::util::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}