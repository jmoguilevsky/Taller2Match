//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_MATCHER_H
#define APPSERVER_MATCHER_H

#include "RequestHandler.h"

class Matcher : public RequestHandler {
	// Se encarga de todo lo relacionado con los matches
private:
	HTTPRequest getDataFromShared();

public:
	HTTPResponse handle();
};

#endif //APPSERVER_MATCHER_H
