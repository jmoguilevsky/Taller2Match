//

#include "RocksDb.h"
#include <iostream>
//
// Created by chris on 13/04/16.
#include <rocksdb/utilities/transaction.h>

RocksDb::RocksDb(const std::string &dbName) {
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, dbName, &db);
    std::cout << "Db " << dbName << " created with status: " << status . ToString() << std::endl;
}

void RocksDb::save(const std::string &key, const std::string &value) {
    // TODO : if (db == NULL) return ERROR;
    db->Put(rocksdb::WriteOptions(), key, value);
    //TODO return status y ver qué pasa
}

bool RocksDb::get(const std::string &key, std::string &value) {
    // TODO : if (db == NULL) return ERROR;
    rocksdb::Status s;
    s = db->Get(rocksdb::ReadOptions(), key, &value);
    //TODO ver qué hacemos con el status, si hace falta
    return s.ok();
}

RocksDb::~RocksDb() {
    delete db;
}

bool RocksDb::hasKey(std::string key) {
    // TODO HACER ESTO BIEN
    std::string value;
    get(key, value);
    return value != "";
}

std::map<std::string, std::string> RocksDb::listAll() {
    rocksdb::Iterator *it = db->NewIterator(rocksdb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
    }
    assert(it->status().ok()); // Check for any errors found during the scan
    delete it;
    return std::map<std::string, std::string>();
}

std::string RocksDb::getLastKey() {
    rocksdb::Iterator *it = db->NewIterator(rocksdb::ReadOptions());
    std::string lastKey;
    it->SeekToLast();
    lastKey = (it->key()).ToString();
    delete it;
    return lastKey;
}