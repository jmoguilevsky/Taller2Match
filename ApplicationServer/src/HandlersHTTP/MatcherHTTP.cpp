//
// Created by chris on 12/05/16.
//

#include "MatcherHTTP.h"

#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_POST "POST"
#define HTTP_DELETE "DELETE"

#define FULL_URI_CANDIDATES "/matches/candidates"
#define FULL_URI_LIKES "/matches/likes"
#define FULL_URI_DISLIKES "/matches/dislikes"
#define FULL_URI_MATCHES "/matches/matches"

HTTPResponse MatcherHTTP::handle(HTTPRequest request) {
    std::string verb = request.getVerb();
    std::string uri = request.getUri();

    if (verb == HTTP_GET && uri == FULL_URI_CANDIDATES) {
        return handleGetCandidate(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_LIKES) {
        return handlePostLikeLastCandidate(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_DISLIKES) {
        return handlePostDislikeLastCandidate(request);
    } else if (verb == HTTP_GET && uri == FULL_URI_MATCHES) {
        return handleGetMatches(request);
    } else {
        return HTTP::NotFound();
    }
}

HTTPResponse MatcherHTTP::handleGetMatches(HTTPRequest &request) {
    return HTTP::OK();
}

HTTPResponse MatcherHTTP::handlePostLikeLastCandidate(HTTPRequest &request) {
    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken;
    validToken = users.getUserId(token, &userId);
    if (!validToken) return HTTP::Unauthorized();
    matcher.postLikeLastCandidate(userId);
    return HTTP::OK();
}

HTTPResponse MatcherHTTP::handleGetCandidate(HTTPRequest &request) {

    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token, &userId);
    if (!validToken) return HTTP::Unauthorized();

    // Ahí podría devolver los Json directamente en vez de UserProfile
    UserProfile candidate = matcher.getNextCandidate(userId);

    // Escribir los perfiles de usuario en un Json grande

    Json::Value user = candidate.getJson();

    std::string userList = util::JsonToString(user);

    return HTTP::OK(userList);
}

HTTPResponse MatcherHTTP::handlePostDislikeLastCandidate(HTTPRequest &request) {
    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token, &userId);
    if (!validToken) return HTTP::Unauthorized();
    matcher.postDislike(userId);
    return HTTP::OK();
}