//
// Created by chris on 25/05/16.
//

#ifndef APPSERVER_JSONARRAYDB_H
#define APPSERVER_JSONARRAYDB_H

//! Base de datos {key,Json array}

#include <string>
#include "RocksDb.h"

class JsonArrayDb {

    RocksDb *database;

public:

    JsonArrayDb(std::string name) {
        database = new RocksDb(name);
    }

    bool has_value(std::string key, std::string value) {
        std::string arrayString;
        database->get(key, arrayString);
        Json::Value arrayJson = util::stringToJson(arrayString);
        Json::ArrayIndex size = arrayJson.size();
        for (int i = 0; i < size; i++) {
            if (arrayJson[i].asString() == value) return true;
        }
        return false;
    }

    void append_value(std::string key, std::string value) {
        // No verifica si el valor ya está o no
        std::string arrayString;
        database->get(key, arrayString);
        Json::Value newArrayJson = util::stringToJson(arrayString);
        Json::Value valueJson = value;
        newArrayJson.append(valueJson);
        std::string newArrayString = util::JsonToString(newArrayJson);
        database->save(key, newArrayString);
    }

    void remove_value(std::string key, std::string value) {
        // No verifica si el valor ya está o no
        std::string arrayString;
        database->get(key, arrayString);
        Json::Value arrayJson = util::stringToJson(arrayString);
        Json::Value newArrayJson;
        Json::ArrayIndex size = arrayJson.size();
        for (int i = 0; i < size; i++) {
            if (arrayJson[i].asString() != value) {
                newArrayJson.append(arrayJson[i]);
            }
        }
        std::string newArrayString = util::JsonToString(newArrayJson);
        database->save(key, newArrayString);
    }

    std::vector<std::string> values(const std::string &key) {
        std::vector<std::string> vec;
        std::string arrayString;
        database->get(key, arrayString);
        Json::Value arrayJson = util::stringToJson(arrayString);
        Json::ArrayIndex size = arrayJson.size();
        for (int i = 0; i < size; i++) {
            vec.push_back(arrayJson[i].asString());
        }
        return vec;
    }

    std::string values_as_string(const std::string &key) {
        std::string values;
        database->get(key, values);
        return values;
    }
};


#endif //APPSERVER_JSONARRAYDB_H
