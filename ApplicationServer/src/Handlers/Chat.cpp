//
// Created by chris on 06/05/16.
//

#include "Chat.h"

Chat::Chat(HTTPRequest request, ChatDB &chatDB, MatchesDB &matchesDb) : Handler(request), chatDB(chatDB),
                                                                        matchesDB(matchesDB) {
}

HTTPResponse Chat::handle() {
	std::string msgStr = request.getBody();
	Json::Value msg = utils::stringToJson(msgStr);
	std::string userA = msg["from"].asString();
	std::string userB = msg["to"].asString();
	if (matchesDB.userMatch(userA, userB)) {
		chatDB.save(userA, userB, msgStr);
	}
}