//
// Created by chris on 12/05/16.
//

#include "ChatHTTP.h"
#include "../Mongoose/MgHTTPClient.h"

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

void *notifyChat(void *msg) {
	Json::Value msgJson = *(Json::Value *) (msg);
	MgHTTPClient client;
	client.connectToUrl(msgJson["url"].asString());
	msgJson.removeMember("url");
	HTTPRequest request("POST", "/chat", util::JsonToString(msgJson));
	HTTPResponse resp = client.sendRequest(request);
	delete ((Json::Value *) msg);
}

HTTPResponse ChatHTTP::handleSendChat(HTTPRequest request) {
	std::string userId;
	std::string token = request.getHeader("Authorization");
	bool validToken = users.getUserId(token, &userId);
	if (!validToken) return HTTP::Unauthorized();

	Json::Value msg = util::stringToJson(request.getBody());
	std::string otherUserId = msg["id"].asString();

	if (!matcher.usersMatch(userId, otherUserId)) {
			return HTTP::Error("User is not a match");
	}

	std::string content = msg["msg"].asString();

	std::string msgJson = chat.sendMessage(userId, otherUserId, content);
	Json::Value notif = util::stringToJson(msgJson);
	notif["url"] = users.getUserURL(otherUserId);
	Json::Value *notification = new Json::Value(notif);
	mg_start_thread(notifyChat, notification);
	return HTTP::OK();
}

HTTPResponse ChatHTTP::handleGetHistory(HTTPRequest request) {
	std::string userId;
	std::string token = request.getHeader("Authorization");
	bool validToken = users.getUserId(token, &userId);
	if (!validToken) return HTTP::Unauthorized();

	Json::Value info = util::stringToJson(request.getBody());
	std::string otherUserId = info["id"].asString();

	if (!matcher.usersMatch(userId, otherUserId)) {
		return HTTP::Error("User is not a match");
	}
	// FIXME que devuelva el Json completo y listo

	std::string history = chat.getHistory(userId, otherUserId);

	return HTTP::OKJson(history);
}