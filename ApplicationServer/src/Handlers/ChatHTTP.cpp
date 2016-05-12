//
// Created by chris on 12/05/16.
//

#include "ChatHTTP.h"

HTTPResponse ChatHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	std::string uri = request.getUri();
	if (verb == "POST" && uri == "/chat") {
		return handleSendChat(request);
	} else if (verb == "GET" && uri == "/chat/unread") {
		return handleGetUnread(request);
	} else {
		return HTTP::BadRequest();
	}
}

HTTPResponse ChatHTTP::handleSendChat(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	ChatMessage msg;
	Json::Value msgJson = utils::stringToJson(request.getBody());
	std::string userFrom = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	msgJson["message"]["from"] = userFrom;
	msgJson["message"]["read"] = "no";
	msg.fromJson(msgJson);
	std::cout << utils::JsonToString(msg.toJson()) << std::endl;
	chat->sendMessage(msg);
	return HTTP::OK();
}

HTTPResponse ChatHTTP::handleGetUnread(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	std::string userB;
	std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();


	std::vector<ChatMessage> unread = chat->getUnread(email, userB);
	Json::Value messages;
	Json::Value array;
	for (int i = 0; i < unread.size(); i++) {
		array.append(unread[i].toJson());
	}
	messages["messages"] = array;
	std::string toSend = utils::JsonToString(messages);
	return HTTP::OKJson(toSend);
}

ChatHTTP::~ChatHTTP() {
	delete chat;
}

ChatHTTP::ChatHTTP(ChatDB &db) {
	chat = new Chat(db);
}