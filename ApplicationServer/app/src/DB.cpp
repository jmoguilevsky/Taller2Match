//

#include "DB.h"

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

std::string DB::get(const std::string &key) {
	// TODO : if (db == NULL) return ERROR;
	std::string value;
	rocksdb::Status s;
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	//TODO ver qué hacemos con el status, si hace falta
	return value;
}

DB::~DB() {
	delete db;
}



