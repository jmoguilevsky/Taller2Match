//
// Created by chris on 12/05/16.
//

#include <iostream>
#include "UsersHTTP.h"
#include "../HTTP/HTTP.h"
#include "../Log/Log.h"

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
    std::cout << "verb:" << "\"" + verb + "\"" << std::endl;
    std::cout << "uri:" << "\"" + uri + "\"" << std::endl;
    if (verb == HTTP_POST && uri == FULL_URI_SIGNUP) {
        std::cout << " >>> SIGNUP <<< " << std::endl;
        return handleSignUp(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_LOGIN) {
        std::cout << " >>> LOGIN <<< " << std::endl;
        return handleLogin(request);
    } else if (verb == HTTP_POST && uri == FULL_URI_LOGOUT) {
        std::cout << " >>> LOGOUT <<< " << std::endl;
        return handleLogout(request);
    } else if (verb == HTTP_DELETE && uri == FULL_URI_PROFILE) {
        std::cout << " >>> DELETE <<< " << std::endl;
        return handleSignUp(request);
    } else if (verb == HTTP_PUT && uri == FULL_URI_PROFILE) {
        std::cout << " >>> UPDATE PROFILE <<< " << std::endl;
        return handleUpdateProfile(request);
    } else if (verb == HTTP_PUT && uri == FULL_URI_PHOTO) {
        std::cout << " >>> UPDATE PHOTO <<< " << std::endl;
        return handleUpdatePhoto(request);
    } else if (verb == HTTP_GET){
        std::cout << " >>> GET PROFILE <<< " << std::endl;
        std::vector<std::string> uriSplit = request.getSplitUri();
        if(uriSplit.size() == 2) {
            return handleViewProfile(request);
        } else {
            return HTTP::NotFound();
        }
    } else {
        return HTTP::NotFound();
    }
}

HTTPResponse UsersHTTP::handleSignUp(HTTPRequest request) {
    std::cout << "req:" << request.toString() << std::endl;
    Json::Value info = util::stringToJson(request.getBody())["info"];
    std::string password = info["password"].asString();

    Json::Value user = util::stringToJson(request.getBody());

    UserProfile userProfile;
    userProfile.fromJson(util::JsonToString(user));

    std::string email = userProfile.getEmail();

    bool signUp_OK = users.signUp(email, password, userProfile);

    if (signUp_OK) {
        return HTTP::OKJson("{}");
    } else {
        return HTTP::Error();
    }
}

HTTPResponse UsersHTTP::handleLogin(HTTPRequest request) {
    std::cout << "req:" << request.toString() << std::endl;
    Json::Value credentials = util::stringToJson(request.getBody());
    std::string email = credentials["email"].asString();
    std::string password = credentials["password"].asString();
    std::string url = credentials["url"].asString();
    std::string token;
    UserProfile prof;

    bool login_OK = users.login(email, password, &token, &prof, url);

    if (!login_OK) {
        return HTTP::Error("User doesn't exist or wrong password, or user already connected!");
    }
    else {
        Json::Value profJson = prof.getJson();
        profJson["token"] = token;
        std::string profileJson = util::JsonToString(profJson);
        Log::info("New user connected");
        return HTTP::OKJson(profileJson);
    }
}

HTTPResponse UsersHTTP::handleUpdateProfile(HTTPRequest request) {
    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token,&userId);
    if(!validToken) return HTTP::Unauthorized();

    Json::Value profileJson = util::stringToJson(request.getBody());
    UserProfile newProfile (profileJson);

    std::cout << "NUEVO PERFIL: " << util::JsonToString(newProfile.getJson()) << std::endl;

    bool ok = users.updateProfile(userId, newProfile);
    if(ok){
        // TODO Log::info("Login de usuario OK"
        return HTTP::OK();
    } else{
        return HTTP::Error();
    }
}

HTTPResponse UsersHTTP::handleUpdatePhoto(HTTPRequest request) {
    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token,&userId);
    if(!validToken) return HTTP::Unauthorized();

    Json::Value newPhoto = util::stringToJson(request.getBody());
    bool ok = users.updatePhoto(userId, newPhoto);
    if(ok){
        return HTTP::OK();
    } else{
        return HTTP::Error();
    }
}

HTTPResponse UsersHTTP::handleViewProfile(HTTPRequest request) {
    // TODO poner los casos: usuario existe pero no es match (Unauthorized) Y usuario no existe (Not Found)

    std::string userId;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token,&userId);
    if(!validToken) return HTTP::Unauthorized();

    std::string otherUserId; // TODO
    if(matcher.usersMatch(userId, otherUserId)){
        // Podría devolver el Json directamente en vez del UserProfile
        UserProfile profile;
        users.getUserProfile(otherUserId, &profile);
        std::string profileStr = util::JsonToString(profile.getJson());
        return HTTP::OKJson(profileStr);
    } else {
        return HTTP::Unauthorized();
    }
}

HTTPResponse UsersHTTP::handleLogout(HTTPRequest request) {
    std::string userId;
    std::cout<<"req:" << request.toString()<<std::endl;
    std::string token = request.getHeader("Authorization");
    bool validToken = users.getUserId(token,&userId);
    std::cout << token;
    if(!validToken) { std::cout<<"no logout"<<std::endl;return HTTP::Unauthorized();}
    std::cout<<"logout"<<std::endl;
    users.logout(token);
    Log::info("User logged out");

    return HTTP::OKJson("{}");
}
