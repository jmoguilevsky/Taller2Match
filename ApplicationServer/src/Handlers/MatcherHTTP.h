//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_MATCHERHTTP_H
#define APPSERVER_MATCHERHTTP_H


#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "Matcher.h"
#include "../HTTP/HTTP.h"

//! Esta clase maneja los request HTTP que tienen que ver con los likes, matches, etc.

class MatcherHTTP {

	Matcher *matcher;

	HTTPResponse handlePostLike(HTTPRequest &request);

	HTTPResponse handleGetCandidates(HTTPRequest &request);

	HTTPResponse handlePostNoMatch(HTTPRequest &request);

public:
	MatcherHTTP(MatchesDB &matchesDB, SharedData &sharedData);

	~MatcherHTTP();

	HTTPResponse handle(HTTPRequest request);
};


#endif //APPSERVER_MATCHERHTTP_H
