//
// Created by chris on 16/04/16.
//

#include "utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#define STR_TO_INT(x) atoi(x.c_str())
#define INT_TO_STR(x) std::to_string(x)

struct tm utils::currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	return tstruct;
}

std::string utils::timeToString(struct tm tstruct) {
	char buf[80];
	strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
	return buf;
}

struct tm utils::stringToTime(std::string c) {
	const char *time_details = c.c_str();
	struct tm tm;
	strptime(time_details, "%d-%m-%Y %X", &tm);
	return tm;
}

int utils::diffTimeInSeconds(struct tm t0, struct tm t1) {
	time_t t0Time = mktime(&t0);
	time_t t1Time = mktime(&t1);
	return difftime(t0Time, t1Time);
}

std::vector<std::string> &utils::split(const std::string &s, char delim,
                                       std::vector<std::string> &elems) {
	// Split para un string por un char. Devuelve un vector con los tokens

	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}