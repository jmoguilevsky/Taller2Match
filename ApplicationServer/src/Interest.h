//
// Created by chris on 07/05/16.
//

#ifndef APPSERVER_INTEREST_H
#define APPSERVER_INTEREST_H


#include "json/json.h"

class Interest {
private:
	std::string value;
	std::string category;
public:
	bool operator<(const Interest &interest) const;

	Interest(Json::Value interest);

	Interest(std::string category, std::string value);

	std::string getCategory() const;

	std::string getValue() const;

};


#endif //APPSERVER_INTEREST_H