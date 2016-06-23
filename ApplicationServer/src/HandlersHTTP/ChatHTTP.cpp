//
// Created by chris on 12/05/16.
//

#include "ChatHTTP.h"
#include "../Mongoose/MgHTTPClient.h"
#include "RequestParser.h"
#include "../Exceptions/AuthorizationException.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define FULL_URI_MESSAGE "/chat/message"
#define FULL_URI_NEW_CHAT "/chat/new"

HTTPResponse ChatHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	std::string uri = request . getUri();

	if (verb == HTTP_POST && uri == FULL_URI_MESSAGE) {
		return handleSendChat(request);
	} else if (verb == HTTP_GET && uri == FULL_URI_NEW_CHAT) {
		return handleGetNew(request);
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
	chat . sendMessage(userId, matchId, message);
	return HTTP::OK(util::stringToJson("{}"));
}

HTTPResponse ChatHTTP::handleGetNew(HTTPRequest request) {
	std::string token;
	RequestParser::parseGetNew(request, &token);
	std::string userId = connected . getUserId(token);
	Json::Value newMsgs = chat . getNewForUser(userId);
	if (newMsgs . size() == 0) { return HTTP::OK(util::stringToJson("{}")); }
	return HTTP::OK(newMsgs);
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