#include <iostream>
#include "UsersHTTP.h"
#include "../HTTP/HTTP.h"
#include "../Log/Log.h"
#include "RequestParser.h"
#include "ResponseFormatter.h"
#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_POST "POST"
#define HTTP_DELETE "DELETE"
#define FULL_URI_SIGNUP "/users/signup"
#define FULL_URI_LOGIN "/users/login"
#define FULL_URI_LOGOUT "/users/logout"
#define FULL_URI_PROFILE "/users/update"
#define FULL_URI_PHOTO "/users/update/photo"

HTTPResponse UsersHTTP::handle(HTTPRequest request) {

    std::string verb = request.getVerb();
    std::string uri = request.getUri();

    if (verb == HTTP_POST && uri == FULL_URI_SIGNUP) {
        //std::cout << " >>> SIGNUP <<< " << std::endl;
        return handleSignUp(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_LOGIN) {
        //std::cout << " >>> LOGIN <<< " << std::endl;
        return handleLogin(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_LOGOUT) {
        //std::cout << " >>> LOGOUT <<< " << std::endl;
        return handleLogout(request);
    } else if (verb == HTTP_DELETE && uri == FULL_URI_PROFILE) {
        //std::cout << " >>> DELETE <<< " << std::endl;
        return handleSignUp(request);
    } else if (verb == HTTP_PUT && uri == FULL_URI_PROFILE) {
        //std::cout << " >>> UPDATE PROFILE <<< " << std::endl;
        return handleUpdateProfile(request);
    } else if (verb == HTTP_PUT && uri == FULL_URI_PHOTO) {
        //std::cout << " >>> UPDATE PHOTO <<< " << std::endl;
        return handleUpdatePhoto(request);
    } else if (verb == HTTP_GET) {
        //std::cout << " >>> GET PROFILE <<< " << std::endl;
        return handleViewProfile(request);
    } else {
        return HTTP::NotFound();
    }
}

HTTPResponse UsersHTTP::handleSignUp(HTTPRequest request) {
    std::string email;
    std::string password;
    UserProfile profile;
    int distance;
    RequestParser::parseSignUp(request, &email, &password, &profile, &distance);
    profilesDatabase . newUser(email, password, profile, distance);
    return HTTP::OK(util::stringToJson("{}"));
}

HTTPResponse UsersHTTP::handleLogin(HTTPRequest request) {
    std::string email;
    std::string password;
    std::string url;
    RequestParser::parseLogin(request, &email, &password, &url);
    bool passOK = profilesDatabase.verify(email, password);
    if (!passOK) return HTTP::Unauthorized();
    std::string userId = profilesDatabase.getUserId(email);
    UserProfile profile = profilesDatabase.getProfile(userId);
    std::string token = connected.login(userId, url);
    return ResponseFormatter::formatLogin(token, profile);
}

HTTPResponse UsersHTTP::handleUpdateProfile(HTTPRequest request) {
    std::string token;
    UserProfile profile;
    RequestParser::parseUpdateProfile(request, &token, &profile);
    std::string userId = connected.getUserId(token);
    profilesDatabase.updateProfile(userId, profile);
    return HTTP::OK(util::stringToJson("{}"));
}

HTTPResponse UsersHTTP::handleUpdatePhoto(HTTPRequest request) {
    std::string token;
    std::string photo;
    RequestParser::parseUpdatePhoto(request, &token,  &photo);
    std::string userId = connected.getUserId(token);
    Json::Value newPhoto = util::stringToJson(request.getBody());
    //users.updatePhoto(userId, newPhoto);
    return HTTP::OK();
}

HTTPResponse UsersHTTP::handleViewProfile(HTTPRequest request) {
    std::string token;
    std::string otherUserId;
    RequestParser::parseViewProfile(request, &token, &otherUserId);
    std::string userId = connected.getUserId(token);
    if(!matcher.usersMatch(userId, otherUserId)) throw AuthorizationException("User is not a match");
    UserProfile profile = profilesDatabase.getProfile(otherUserId);
    return ResponseFormatter::formatViewProfile(profile);
}

HTTPResponse UsersHTTP::handleLogout(HTTPRequest request) {
    std::string token;
    RequestParser::parseLogout(request, &token);
    connected.logout(token);
    return HTTP::OK();
}
