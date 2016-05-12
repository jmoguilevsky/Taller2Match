//

#include "RocksDB.h"
#include <iostream>
//
// Created by chris on 13/04/16.

RocksDB::RocksDB(const std::string &dbName) {
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, dbName, &db);
}

void RocksDB::save(const std::string &key, const std::string &value) {
	// TODO : if (db == NULL) return ERROR;
	rocksdb::Status s;
	s = db->Put(rocksdb::WriteOptions(), key, value);
	//TODO return status y ver qué pasa
}


bool RocksDB::get(const std::string &key, std::string &value) {
	// TODO : if (db == NULL) return ERROR;
	rocksdb::Status s;
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	//TODO ver qué hacemos con el status, si hace falta
	return s.ok();
}

RocksDB::~RocksDB() {
	delete db;
}

bool RocksDB::keyExists(std::string key) {
	// TODO HACER ESTO BIEN
	std::string value;
	get(key, value);
	return value != "";
}

std::map<std::string, std::string> RocksDB::listAll() {
	rocksdb::Iterator *iter = db->NewIterator(rocksdb::ReadOptions());
	iter->SeekToFirst();
	while (iter->Valid()) {
		rocksdb::Slice key = iter->key();
		rocksdb::Slice value = iter->value();
		std::cout << key.ToString() << " : " << value.ToString() << std::endl;
		iter->Next();
	}
}

std::vector<std::string> RocksDB::keys() {
	rocksdb::Iterator *iter = db->NewIterator(rocksdb::ReadOptions());
	iter->SeekToFirst();
	std::vector<std::string> v;
	while (iter->Valid()) {
		rocksdb::Slice key = iter->key();
		v.push_back(key.ToString());
		iter->Next();
	}
	return v;
}