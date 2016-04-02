#include "rocksdb/db.h"
#include <iostream>

int main(){
	rocksdb::DB* db;
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, "testdb", &db);
	std::string key1;
	std::string key2;
	std::string value;
	rocksdb::Status s;
	key1 = "AAA";
	value = "1234";

	//Usar esta linea para guardar el par key1,value en la db.
//	s = db -> Put(rocksdb::WriteOptions(),key1,value);

	//Usar esta linea para leer el valor asociado al key1 y guardarlo en value.
	s = db -> Get(rocksdb::ReadOptions(),key1,&value);

	std::cout << "Valor: " << value << std::endl;

	key1 = "BBB";
	s = db -> Get(rocksdb::ReadOptions(),key1,&value);

	std::cout << "Valor: " << value << std::endl;

	delete db;
}
