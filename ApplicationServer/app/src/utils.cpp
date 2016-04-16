//
// Created by chris on 16/04/16.
//

#include "utils.h"
#include <string>
#include <sstream>
#include "../mongoose-master/mongoose.h"

std::string utils::bufToString(struct mg_connection* connection){
	struct mbuf* io = &(connection->recv_mbuf);
	std::string str = io -> buf;
	str[str.size()-1] = '\0';
	mbuf_remove(io, io->len);
	return str;
}

std::vector<std::string>& utils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	// Split para un string por un char. Devuelve un vector con los tokens

	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//TODO todos los métodos que siguen podrían estar en la clase DB, pero da igual.

bool utils::valueInDBList(DB* db, const std::string& user1, const std::string& user2){
	// Devuelve true si user2 ya está en el value del user1 en la db.

	std::vector<std::string> userList = utils::valuesAsVector(db,user1);

	for(int i = 0; i < userList.size(); i++){
		if(userList[i] == user2){
			return true;
		}
	}

	return false;
}

void utils::appendValue(DB* db, const std::string& user1, const std::string& user2){
	// Agrega el id del user2 a la db para el user1.
	db->save(user1, db->get(user1) + "," + user2);
}


void utils::removeValue(DB* db, const std::string & user1, const std::string& user2){
	// Borra user2 de la lista de valores para user1 en la db.
	std::vector<std::string> values = valuesAsVector(db,user1);
	std::vector<std::string> newValues;
	std::string aux;
	for(int i = 0; i < values.size(); i++){
		aux = values[i];
		if(aux != user2) newValues.push_back(aux);
	}
	std::string newValuesString;
	for(int i = 0; i < newValues.size() - 1; i++){
		newValuesString += newValues[i] + ",";
	}
	newValuesString += newValues[newValues.size()-1];
	db->save(user1,newValuesString);
}

std::vector<std::string> utils::valuesAsVector(DB* db, const std::string& user1){
	std::string s = db->get(user1);
	std::vector<std::string> users;
	utils::split(s,',',users);
	return users;
}

