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
	//! Handler para que un usuario pueda "reaccionar" (aceptar o rechazar) a otro usuario.
	HTTPResponse handlePostReaction(HTTPRequest request);
	//! Handler para obtener un nuevo candidato a match para un usuario.
	HTTPResponse handleGetCandidate(HTTPRequest request);
	//! Handler para que un usuario pueda obtener todos los perfiles de todos sus matches.
	HTTPResponse handleGetMatches(HTTPRequest request);
	//! Handler para que un usuario pueda ver el perfil de uno de sus matches.
	HTTPResponse handleViewProfile(HTTPRequest request);

public:

	MatchHTTP(ProfilesDatabase &users, Matcher &matcher, ConnectedUsers &connected)
			: users(users), matcher(matcher), connected(connected) {};

	HTTPResponse handle(HTTPRequest request);

	HTTPResponse handleGetAllInterests(HTTPRequest request);
};


#endif //APPSERVER_MATCHERHTTP_H
