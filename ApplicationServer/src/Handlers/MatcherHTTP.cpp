//
// Created by chris on 12/05/16.
//

#include "MatcherHTTP.h"

HTTPResponse MatcherHTTP::handle(HTTPRequest request) {
	std::string verb = request.getVerb();
	std::string uri = request.getUri();
	std::string email;
	if (verb == "GET" && uri == "/matches/candidates") {
		return handleGetCandidates(request);
	} else if (verb == "POST" && uri == "/matches/like") {
		return handlePostLike(request);
	} else if (verb == "POST" && uri == "/matches/nomatch") {
		return handlePostNoMatch(request);
	} else {
		return HTTP::BadRequest();
	}
}

HTTPResponse MatcherHTTP::handlePostLike(HTTPRequest &request) {
	std::map<std::string, std::string> headers;
	std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	Json::Value userInfo = utils::stringToJson(request.getBody());
	std::string userB = userInfo["user"]["email"].asString();
	int code = matcher->postLike(email, userB);
	return HTTP::OK();
}

HTTPResponse MatcherHTTP::handleGetCandidates(HTTPRequest &request) {
	std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	std::vector<UserProfile> candidates = matcher->getCandidates(email);
	// Escribir los perfiles de usuario en un Json grande
	Json::Value users;
	Json::Value array;
	for (int i = 0; i < candidates.size(); i++) {
		const Json::Value &json = candidates[i].getJson();
		array.append(json);
	}
	users["users"] = array;
	std::string userList = utils::JsonToString(users);
	return HTTP::OK(userList);
}

HTTPResponse MatcherHTTP::handlePostNoMatch(HTTPRequest &request) {
	std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	Json::Value userInfo = utils::stringToJson(request.getBody());
	std::string userB = userInfo["user"]["email"].asString();
	int code = matcher->postNoMatch(email, userB);
	return HTTP::OK();
}

MatcherHTTP::MatcherHTTP(MatchesDB &matchesDB, SharedData &sharedData) {
	matcher = new Matcher(matchesDB, sharedData);
}

MatcherHTTP::~MatcherHTTP() {
	delete matcher;
}