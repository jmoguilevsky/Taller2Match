//
// Created by chris on 24/04/16.
//

#include <iostream>
#include "Matcher.h"
#include "../UserProfile.h"

HTTPResponse Matcher::handle() {
	if (request.getVerb() == "GET" && request.getUri() == "/candidates") {
		return getCandidates();
	}
	if (request.getVerb() == "") { }

}

HTTPResponse Matcher::getCandidates() {
	Json::Value usersList = sharedData.getUsersList();
	std::map<std::string, UserProfile> candidates;
	Json::Value retUsers;
	Json::Value array;


	for (int i = 0; i < usersList.size(); i++) {
		// Parseo los perfiles de todos los usuarios
		if (i < 2) array.append(usersList["users"][i]);
		UserProfile userProfile(usersList["users"][i]["user"]);
		candidates[userProfile.getId()] = userProfile;
	}
	filterCandidates(candidates);
	retUsers["users"] = array;
	std::map<std::string, std::string> headers;
	headers["Content-type"] = "application/json";

	return HTTPResponse("200", "OK", headers,
	                    utils::JsonToString(retUsers));
}

void Matcher::filterCandidates(std::map<std::string, UserProfile> &candidates) {

}

Matcher::Matcher(HTTPRequest request, MatchesDB &db,
                 SharedData &sharedData) : Handler(
		request),
                                                         db(db), sharedData(
				sharedData) {
}