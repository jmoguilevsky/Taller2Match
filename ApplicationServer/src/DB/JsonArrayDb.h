//
// Created by chris on 25/05/16.
//

#ifndef APPSERVER_JSONARRAYDB_H
#define APPSERVER_JSONARRAYDB_H

#include <string>
#include "RocksDb.h"

//! Base de datos {clave, valor}, donde el valor es un array Json.

class JsonArrayDb {

    RocksDb *database;

public:

    //! Constructor, recibe el nombre de la base de datos a abrir/crear.
    JsonArrayDb(std::string name);

    //! True si en el array Json asociado a la clave existe el valor, False si no.
    bool has_value(std::string key, std::string value);

    //! Agrega el valor al array Json asociado a la clave.
    void append_value(std::string key, std::string value);

    //! Elimina el valor del array Json asociado a la clave.
    void remove_value(std::string key, std::string value);

    //! Devuelve valores del array Json asociado a la clave.
    std::vector<std::string> values(const std::string &key);

    //! Devuelve el array Json asociado a la clave, como un string.
    std::string values_as_string(const std::string &key);

    void erase_key(std::string key);
};


#endif //APPSERVER_JSONARRAYDB_H
