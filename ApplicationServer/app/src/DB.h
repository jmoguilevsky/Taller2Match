//
// Created by chris on 13/04/16.
//

#ifndef APPLICATIONSERVER_DB_H
#define APPLICATIONSERVER_DB_H

#include <rocksdb/db.h>

// Esta clase lo único que hace es guardar y leer datos de una base de datos.

class DB {
	rocksdb::DB* db;
public:
	DB(const std::string & dbName);
	void save(const std::string &key, const std::string &value);
	std::string get(const std::string &key);
	~DB();

};


#endif //APPLICATIONSERVER_DB_H
