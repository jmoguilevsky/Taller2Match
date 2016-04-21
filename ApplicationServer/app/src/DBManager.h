//
// Created by chris on 12/04/16.
//

#ifndef APPLICATIONSERVER_DBHANDLER_H
#define APPLICATIONSERVER_DBHANDLER_H

#include "rocksdb/db.h"
#include "utils.h"
#include "DB.h"

class DBManager {

	static DB *likes; //Usuarios que YO acepté
	static DB *noMatches; //Usuarios que YO rechacé.
	static DB *matches; // Matches

private:
	DBManager();

public:

	// TODO cambiar el nombre, es medio fuerte el "reject", jaja

	static void initDBs(const std::string &likesDBName,
	                    const std::string &matchesDBName,
	                    const std::string &noMatchesDBName);

	static int likeUser(const std::string &user1,
	                    const std::string &user2);

	static int rejectUser(const std::string &user1,
	                      const std::string &user2);

	static std::vector<std::string> getLikes(const std::string &user);

	static std::vector<std::string> getMatches(const std::string &user);

	static std::vector<std::string> getNoMatches(
			const std::string &user);

	static void closeDBs();
};


#endif //APPLICATIONSERVER_DBHANDLER_H
