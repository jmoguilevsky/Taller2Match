//
// Created by chris on 12/05/16.
//

#include "ChatHTTP.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"

HTTPResponse ChatHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	std::string uri = request.getUri();

	std::vector<std::string> uriSplit;
	uriSplit = request.getSplitUri();

	if (verb == HTTP_POST && uriSplit.size() == 3 &&  uriSplit[1] == "me") {
		return handleSendChat(request);
	} else if (verb == HTTP_GET && uriSplit.size() == 3 &&  uriSplit[1] == "me") {
		return handleGetHistory(request);
	} else {
		return HTTP::NotFound();
	}
}

HTTPResponse ChatHTTP::handleSendChat(HTTPRequest request) {
	std::vector<std::string> uriSplit;
	uriSplit = request.getSplitUri();

	std::string userId;
	std::string token = request.getHeader("Authorization");
	bool validToken = users.getUserId(token, &userId);
	if (!validToken) return HTTP::Unauthorized();


	std::string otherUserId = uriSplit[2];
	if (!users.userExists(otherUserId)) {
		return HTTP::Error("User doesn't exist");
	} else {
		if (!matcher.usersMatch(userId, otherUserId)) {
			return HTTP::Error("User is not a match");
		}
	}

	std::string content = request.getBody();

	chat.sendMessage(userId, otherUserId, content);

	return HTTP::OK();
}

HTTPResponse ChatHTTP::handleGetHistory(HTTPRequest request) {
	std::vector<std::string> uriSplit;
	uriSplit = request.getSplitUri();

	std::string userId;
	std::string token = request.getHeader("Authorization");
	bool validToken = users.getUserId(token,&userId);
	if(!validToken) return HTTP::Unauthorized();

	std::string otherUserId = uriSplit[2];
	if(!users.userExists(otherUserId)){
		return HTTP::Error("User doesn't exist");
	}else{
		if(!matcher.usersMatch(userId, otherUserId)){
			return HTTP::Error("User is not a match");
		}
	}

	// FIXME que devuelva el Json completo y listo

	std::string history = chat.getHistory(userId, otherUserId);

	return HTTP::OKJson(history);
}