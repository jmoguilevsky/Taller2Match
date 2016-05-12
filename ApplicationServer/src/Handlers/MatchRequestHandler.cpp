#include "MatchRequestHandler.h"
#include "../DB/ChatMessage.h"

#define URI_MATCHER "matches"
#define URI_CHAT "chat"
#define URI_USERS "users"

#define REQ_USERS 1
#define REQ_MATCHER 2
#define REQ_CHAT 3

// TODO: Para cada una de estas funciones, chequear los casos de error.

MatchRequestHandler::MatchRequestHandler(DBManager &dbManager, SharedData &sharedData) {
	users = new UsersHTTP(dbManager.getLoginDB(), sharedData);
	matcher = new MatcherHTTP(dbManager.getMatchesDB(), sharedData);
	chat = new ChatHTTP(dbManager.getChatDB());
	handlers[URI_USERS] = REQ_USERS;
	handlers[URI_MATCHER] = REQ_MATCHER;
	handlers[URI_CHAT] = REQ_CHAT;
}

HTTPResponse MatchRequestHandler::handle(HTTPRequest &request) {
	std::string uri = request.getUri();

	std::vector<std::string> uriVec;
	utils::split(uri, '/', uriVec);

	for (int i = 0; i < uriVec.size(); i++) {
		std::cout << uriVec[i] << std::endl;
	}

	int requestType = handlers[uriVec[1]];
	std::cout << "URI VEC 0" << uriVec[1] << std::endl;
	std::cout << "REQ_TYPE: " << requestType << std::endl;

	if (requestType != REQ_USERS && requestType != REQ_MATCHER && requestType != REQ_CHAT) {
		return HTTP::BadRequest();
	}

	if (uri != "/users/login" && uri != "users/signup") {
		bool credentialsOK = users->verifyCredentials(request);
		if (!credentialsOK)
			return HTTP::Unauthorized();
	}
	switch (requestType) {
		case REQ_USERS:
			return users->handle(request);
		case REQ_MATCHER:
			return matcher->handle(request);
		case REQ_CHAT:
			return chat->handle(request);
		default:
			return HTTP::BadRequest();
	}
}

