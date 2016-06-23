//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_REQUESTPARSER_H
#define APPSERVER_REQUESTPARSER_H


#include "../HTTP/HTTPRequest.h"
#include "../Profile/UserProfile.h"
#include <iostream>
#include "../HTTP/HTTP.h"

#define HTTP_GET "GET"
#define HTTP_PUT "PUT"
#define HTTP_POST "POST"
#define HTTP_DELETE "DELETE"
#define FULL_URI_SIGNUP "/users/signup"
#define FULL_URI_LOGIN "/users/login"
#define FULL_URI_LOGOUT "/users/logout"
#define FULL_URI_PROFILE "/users/update"
#define FULL_URI_PHOTO "/users/update/photo"

namespace RequestParser{

    void parseSignUp(HTTPRequest request, std::string *email, std::string *password, UserProfile *profile,
                     int *distance);

    void parseUpdateProfile(HTTPRequest request, std::string* token, UserProfile* profile);

    void parseUpdatePhoto(HTTPRequest request, std::string* token, std::string* photo);

    void parseViewProfile(HTTPRequest request, std::string* token, std::string* userId);

    void parseLogout(HTTPRequest request, std::string* token);

    void parseLogin(HTTPRequest request, std::string* email, std::string* password, std::string* url);

    void parseGetMatches(HTTPRequest &request);

    void parsePostReaction(HTTPRequest &request, std::string* token, std::string* candidateId, std::string* reaction);

    void parseGetCandidate(HTTPRequest &request, std::string* token);

    void parseSendChat(HTTPRequest request, std::string* token, std::string* candId, std::string* message);

    void parseGetHistory(HTTPRequest request, std::string* token, std::string* candId);

    void parseToken(HTTPRequest request, std::string *token);
};


#endif //APPSERVER_REQUESTPARSER_H
