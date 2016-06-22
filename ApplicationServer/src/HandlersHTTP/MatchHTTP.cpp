//
// Created by chris on 12/05/16.
//

#include "MatchHTTP.h"
#include "RequestParser.h"

#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_POST "POST"
#define HTTP_DELETE "DELETE"

#define FULL_URI_CANDIDATES "/match/candidate"
#define FULL_URI_REACTION "/match/reaction"
#define FULL_URI_MATCHES "/match/matches"
#define FULL_URI_INTERESTS "/match/interests"

HTTPResponse MatchHTTP::handle(HTTPRequest request) {
    std::string verb = request.getVerb();
    std::string uri = request.getUri();
    std::cout<< "ffff "  << uri;
    if (verb == HTTP_GET && uri == FULL_URI_CANDIDATES) {
        return handleGetCandidate(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_REACTION) {
        return handlePostReaction(request);
    } else if (verb == HTTP_GET && uri == FULL_URI_MATCHES) {
        return handleGetMatches(request);
    } else if (verb == HTTP_GET && uri == FULL_URI_INTERESTS) {
        return handleGetAllInterests(request);
    } else {
        return HTTP::NotFound();
    }
}

HTTPResponse MatchHTTP::handleGetMatches(HTTPRequest request) {
    std::string token;
    RequestParser::parseToken(request, &token);
    std::string userId = connected.getUserId(token);
    std::vector<std::string> matches = matcher.getMatches(userId);
    std::string answer;
    for(int i = 0; i < matches.size(); i++){
        answer += matches[i] + ",";
    }
    return HTTP::OK(answer);
}

HTTPResponse MatchHTTP::handlePostReaction(HTTPRequest request) {
    std::string token;
    std::string candidateId;
    std::string reaction;
    RequestParser::parsePostReaction(request, &token, &candidateId, &reaction);
    std::string userId = connected.getUserId(token);
    matcher.postReaction(userId, candidateId, reaction);
    bool isMatch = matcher.usersMatch(userId, candidateId);
    std::string isMatchStr = isMatch?"Match!":"No match yet";
    return HTTP::OK(isMatchStr);
}

HTTPResponse MatchHTTP::handleGetCandidate(HTTPRequest request) {
    std::string token;
    RequestParser::parseGetCandidate(request, &token);
    std::string userId = connected.getUserId(token);
    UserProfile candidate = matcher.getNextCandidate(userId);
    Json::Value user = candidate.getJson();
    return HTTP::OK(user);
}


HTTPResponse MatchHTTP::handleGetAllInterests(HTTPRequest request){
    std::vector<Interest> interests = matcher.getAllInterests();
    Json::Value interestsJson;
    Json::Value array;
    for (int i = 0; i < interests.size(); i++){
        array.append(interests[i].getJson());
    }
    interestsJson["interests"] = array;
    return HTTP::OK(interestsJson);
}