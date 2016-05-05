//
// Created by chris on 24/04/16.
//

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
	for (int i = 0; i < usersList.size(); i++) {
		// Parseo los perfiles de todos los usuarios
		UserProfile userProfile(usersList[i]["user"]);
		candidates[userProfile.getId()] = userProfile;
	}
	std::map<std::string, std::string> headers;
	headers["Content-type"] = "application/json";
	return HTTPResponse("200", "OK", headers,
	                    "{\"users\":[{\"user\":{\"name\":\"pepe\"}},{\"user\":{\"name\":\"juan\"}}]}");
}


Matcher::Matcher(HTTPRequest request, MatchesDB &db,
                 SharedData &sharedData) : Handler(
		request),
                                                         db(db), sharedData(
				sharedData) {
}