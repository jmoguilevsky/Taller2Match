//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_UTILS_H
#define MULTITHREADMULTICONNECTION_UTILS_H
#include <string>
#include "DB.h"
#include "../mongoose-master/mongoose.h"
namespace utils {
	std::string bufToString(struct mg_connection *connection);

	bool valueInDBList(DB* db, const std::string &user1, const std::string &user2);

	void appendValue(DB* db, const std::string &user1, const std::string &user2);

	void removeValue(DB* db, const std::string &user1, const std::string &user2);

	std::vector<std::string> valuesAsVector(DB* db, const std::string &user1);

	std::vector<std::string> & split(const std::string &s, char delim,
	                                 std::vector<std::string> &elems);
}
#endif //MULTITHREADMULTICONNECTION_UTILS_H
