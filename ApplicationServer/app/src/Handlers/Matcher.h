//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "RequestHandler.h"
#include "../DB/MatchesDB.h"
#include "../SharedServerConnection.h"

//! Handler para los requests relacionados con likes y matches.
class Matcher : public RequestHandler {
	// Se encarga de todo lo relacionado con los matches
private:
	MatchesDB &db;
	SharedServerConnection &sharedServer;
public:
	Matcher(HTTPRequest request, MatchesDB &db,
	        SharedServerConnection &sharedServer);
	HTTPResponse handle();

	HTTPResponse getCandidates();
};

#endif //APPSERVER_MATCHER_H
