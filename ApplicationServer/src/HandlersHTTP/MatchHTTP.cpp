//
// Created by chris on 12/05/16.
//

#include "MatchHTTP.h"
#include "RequestParser.h"

#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_POST "POST"
#define HTTP_DELETE "DELETE"

#define FULL_URI_CANDIDATES "/matches/candidates"
#define FULL_URI_REACTION "/matches/reaction"
#define FULL_URI_MATCHES "/matches/matches"

HTTPResponse MatchHTTP::handle(HTTPRequest request) {
    std::string verb = request.getVerb();
    std::string uri = request.getUri();

    if (verb == HTTP_GET && uri == FULL_URI_CANDIDATES) {
        return handleGetCandidate(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_REACTION) {
        return handlePostReaction(request);
    } else if (verb == HTTP_GET && uri == FULL_URI_MATCHES) {
        return handleGetMatches(request);
    } else {
        return HTTP::NotFound();
    }
}

HTTPResponse MatchHTTP::handleGetMatches(HTTPRequest request) {
    return HTTP::OK();
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
