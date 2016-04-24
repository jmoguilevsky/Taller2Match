//
// Created by chris on 12/04/16.
//

#ifndef APPLICATIONSERVER_DBHANDLER_H
#define APPLICATIONSERVER_DBHANDLER_H

#include "rocksdb/db.h"
#include "../utils.h"
#include "DB.h"

class DBManager {

	DB *likes; //Usuarios que YO acepté
	DB *noMatches; //Usuarios que YO rechacé.
	DB *matches; // Matches
	DB *likeLimit;
	DB *likesReceived;
	DB *credentials;
public:

	// TODO cambiar el nombre, es medio fuerte el "reject", jaja

	void initDBs(const std::string &likesDBName,
	             const std::string &matchesDBName,
	             const std::string &noMatchesDBName);

	int likeUser(const std::string &user1,
	             const std::string &user2);

	int rejectUser(const std::string &user1,
	               const std::string &user2);

	std::vector<std::string> getLikes(const std::string &user);

	std::vector<std::string> getMatches(const std::string &user);

	std::vector<std::string> getNoMatches(
			const std::string &user);

	void closeDBs();

	int getLikesReceived(const std::string &user);


	std::string login(const std::string &user, const std::string &pass);
};


#endif //APPLICATIONSERVER_DBHANDLER_H
