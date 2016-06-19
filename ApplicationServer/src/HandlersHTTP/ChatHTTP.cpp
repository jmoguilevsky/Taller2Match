//
// Created by chris on 12/05/16.
//

#include "ChatHTTP.h"
#include "../Mongoose/MgHTTPClient.h"
#include "RequestParser.h"
#include "../Exceptions/AuthorizationException.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"

HTTPResponse ChatHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	if (verb == HTTP_POST) {
		return handleSendChat(request);
	} else if (verb == HTTP_GET) {
		return handleGetHistory(request);
	} else {
		return HTTP::NotFound();
	}
}

HTTPResponse ChatHTTP::handleSendChat(HTTPRequest request) {
	std::string token;
	std::string matchId;
	std::string message;
	RequestParser::parseSendChat(request, &token, &matchId, &message);
	std::string userId = connected.getUserId(token);
	if (!matcher.usersMatch(userId, matchId)) throw AuthorizationException("User is not a match");
	std::string msgJson = chat.sendMessage(userId, matchId, message);
	return HTTP::OK();
}

HTTPResponse ChatHTTP::handleGetHistory(HTTPRequest request) {
	std::string token;
	std::string matchId;
	RequestParser::parseGetHistory(request, &token, &matchId);
	std::string userId = connected.getUserId(token);
	if (!matcher.usersMatch(userId, matchId)) throw AuthorizationException("User is not a match");
	Json::Value history = chat.getHistory(userId, matchId);
	return HTTP::OK(history);
}