//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "Handler.h"
#include "../DB/MatchesDB.h"
#include "../SharedServerConnection.h"
#include "../UserProfile.h"

//! Handler para los requests relacionados con likes y matches.
class Matcher : public Handler {
	// Se encarga de todo lo relacionado con los matches
private:
	MatchesDB &db;
	SharedData &sharedData;
public:
	Matcher(HTTPRequest request, MatchesDB &db,
	        SharedData &data);
	HTTPResponse handle();

	HTTPResponse getCandidates();

	void filterCandidates(std::map<std::string, UserProfile> &candidates);
};

#endif //APPSERVER_MATCHER_H
