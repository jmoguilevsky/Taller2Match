//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_NOSQLDATABASE_H
#define APPSERVER_NOSQLDATABASE_H

#include <string>
#include "../json/json.h"
#include "../utils.h"
// PARA PODER HACER MOCK DE BASE DE DATOS {key,value}, por ejemplo con un map



class NoSQLDatabase {

public:
	//! Guarda en la DB el par {key,value}
	virtual void save(const std::string &key, const std::string &value) = 0;

//! Devuelve true si key existe como clave en la DB. False si no.
	virtual bool keyExists(std::string basic_string) = 0;

	//! Si key existe en la DB, devuelve true y asigna a value el valor asociado. Si no existe, devuelve false, y no modifica value.
	virtual bool get(const std::string &key, std::string &value) = 0;

	virtual std::map<std::string, std::string> listAll() = 0;

	virtual std::vector<std::string> keys() = 0;
};

bool valueExists(NoSQLDatabase &db, std::string key, std::string value);

void append(NoSQLDatabase &db, std::string key, Json::Value value);
#endif //APPSERVER_NOSQLDATABASE_H
