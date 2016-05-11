//
// Created by chris on 08/05/16.
//

#ifndef APPSERVER_JSONLIST_H
#define APPSERVER_JSONLIST_H

#include <string>
#include <vector>

class JsonList {
	std::vector<std::__cxx11::string> users;
public:
	JsonList(std::__cxx11::string jsonList);

	void append(std::__cxx11::string str);

	bool hasValue(std::__cxx11::string str);

	std::__cxx11::string asString();
};

#endif //APPSERVER_JSONLIST_H
