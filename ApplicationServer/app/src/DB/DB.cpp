//

#include "DB.h"
#include <iostream>
//
// Created by chris on 13/04/16.

DB::DB(const std::string &dbName) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, dbName, &db);
}

void DB::save(const std::string &key, const std::string &value) {
	// TODO : if (db == NULL) return ERROR;
	rocksdb::Status s;
	s = db->Put(rocksdb::WriteOptions(), key, value);
	//TODO return status y ver qué pasa
}


bool DB::get(const std::string &key, std::string &value) {
	// TODO : if (db == NULL) return ERROR;
	rocksdb::Status s;
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	//TODO ver qué hacemos con el status, si hace falta
	return s.ok();
}

DB::~DB() {
	delete db;
}

bool DB::keyExists(std::string basic_string) {
	// TODO HACER ESTO BIEN
	std::string value;
	get(basic_string, value);
	return value != "";
}





