//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_MATCHERHTTP_H
#define APPSERVER_MATCHERHTTP_H

#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "../Handlers/Matcher.h"
#include "../HTTP/HTTP.h"
#include "../Handlers/Users.h"

//! Esta clase maneja los request HTTP que tienen que ver con los likes, matches, etc.

class MatcherHTTP {

	Users& users;

	Matcher& matcher;

	HTTPResponse handlePostLikeLastCandidate(HTTPRequest &request);

	HTTPResponse handleGetCandidate(HTTPRequest &request);

	HTTPResponse handlePostDislikeLastCandidate(HTTPRequest &request);

public:
	MatcherHTTP(Users& users, Matcher& matcher): users(users), matcher(matcher){};

	HTTPResponse handle(HTTPRequest request);

	HTTPResponse handleGetMatches(HTTPRequest &request);
};


#endif //APPSERVER_MATCHERHTTP_H
