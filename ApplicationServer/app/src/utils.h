//
// Created by chris on 16/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_UTILS_H
#define MULTITHREADMULTICONNECTION_UTILS_H

#include "mongoose-master/mongoose.h"
#include <string>
#include <vector>

namespace utils {
	std::string bufToString(struct mg_connection *connection);

	std::vector<std::string> &split(const std::string &s, char delim,
	                                std::vector<std::string> &elems);

	std::vector<std::string> vectorIntersection(std::vector<std::string> &v1,
	                                            std::vector<std::string> &v2);

	tm currentDateTime();

	tm currentDateTime() {
		return tm();
	}

	std::string timeToString(tm tstruct);

	std::string timeToString(tm tstruct) {
		return __cxx11::basic_string < char, char_traits < char >, allocator <
		                                                           char >> ();
	}

	tm stringToTime(std::string c);

	tm stringToTime(std::string c) {
		return tm();
	}

	int diffTimeInSeconds(tm t0, tm t1);

	int diffTimeInSeconds(tm t0, tm t1) {
		return 0;
	}
}
#endif //MULTITHREADMULTICONNECTION_UTILS_H
