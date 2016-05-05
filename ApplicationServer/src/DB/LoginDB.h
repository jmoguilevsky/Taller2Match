//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_LOGINDB_H
#define APPSERVER_LOGINDB_H


#include <iostream>
#include "RocksDB.h"

#define USER_ALREADY_EXISTS 1
#define USER_CREATED_OK 0

#define USER_DOESNT_EXIST 2
#define WRONG_PASSWORD 1
#define LOGIN_OK 0

//! Manejo de login y altas de usuarios en la base de datos de usuarios.
class LoginDB {
	NoSQLDatabase& db;
public:
	//! Abre una DB para datos de login con el nombre name.
	LoginDB(NoSQLDatabase& db) : db(db) {
	}

	//! Crea un nuevo usuario con user y pass. Devuelve USER_ALREADY_EXISTS o USER_CREATED_OK.
	int newUser(std::string user, std::string pass);

	//! Loguea al user con la pass. Devuelve USER_DOESNT_EXIST, WRONG_PASSWORD, o LOGIN_OK según el caso.
	int login(std::string user, std::string pass);
};

#endif //APPSERVER_LOGINDB_H
