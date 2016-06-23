//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_MATCHERHTTP_H
#define APPSERVER_MATCHERHTTP_H

#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "../HTTP/HTTP.h"
#include "../MatchData/ProfilesDatabase.h"
#include "../MatchData/Matcher.h"
#include "../MatchData/ConnectedUsers.h"

//! Esta clase maneja los request HTTP que tienen que ver con los likes, matches, etc.

class MatchHTTP {

	ProfilesDatabase& users;

	Matcher& matcher;

	ConnectedUsers& connected;

	HTTPResponse handlePostReaction(HTTPRequest request);

	HTTPResponse handleGetCandidate(HTTPRequest request);

	HTTPResponse handleGetMatches(HTTPRequest request);

  HTTPResponse handleViewProfile(HTTPRequest request);

public:

	MatchHTTP(ProfilesDatabase &users, Matcher &matcher, ConnectedUsers &connected)
			: users(users), matcher(matcher), connected(connected) {};

	HTTPResponse handle(HTTPRequest request);

	HTTPResponse handleGetAllInterests(HTTPRequest request);
};


#endif //APPSERVER_MATCHERHTTP_H
