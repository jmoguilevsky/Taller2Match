//
// Created by chris on 13/04/16.
//

#ifndef APPLICATIONSERVER_DB_H
#define APPLICATIONSERVER_DB_H

#include <rocksdb/db.h>
#include "KeyValueDB.h"

//! Wrapper para una Base de datos RocksDB.

class RocksDB : public KeyValueDB {
	rocksdb::DB *db;
public:
	//! Abre una base de datos RocksDB con el nombre dbName. Si no existe, la crea.
	RocksDB(const std::string &dbName);

	//! Guarda en la DB el par {key,value}
	void save(const std::string &key, const std::string &value);

	//! Cierra la base de datos.
	~RocksDB();

	//! Devuelve true si key existe como clave en la DB. False si no.
	bool keyExists(std::string key);

	//! Si key existe en la DB, devuelve true y asigna a value el valor asociado. Si no existe, devuelve false, y no modifica value.
	bool get(const std::string &key, std::string &value);

	std::map<std::string, std::string> listAll();

	std::vector<std::string> keys();
};


#endif //APPLICATIONSERVER_DB_H
