//
// Created by chris on 24/04/16.
//

#include "Server.h"
#include "HTTPMessageBuilder.h"

std::map<std::string, std::string> HTTPMessageBuilder::headers;

HTTPRequest HTTPMessageBuilder::getNewInterest(std::string interestJson) {
	return HTTPRequest("POST", "/interests", headers,
	                   interestJson);
}

HTTPRequest HTTPMessageBuilder::getInterestList() {
	return HTTPRequest("GET", "/interests", headers, "");
}

HTTPRequest HTTPMessageBuilder::getDeleteUser(std::string userId) {
	return HTTPRequest("DELETE", "/users/" + userId, headers, "");
}

HTTPRequest HTTPMessageBuilder::getChangeProfilePhoto(std::string userId,
                                                      std::string photoJson) {
	return HTTPRequest("PUT", "/users/" + userId + "/photo",
	                   headers, photoJson);
}

HTTPRequest HTTPMessageBuilder::getModifyUserProfile(std::string userId,
                                                     std::string userProfileJson) {
	return HTTPRequest("PUT", "/users/" + userId, headers, userProfileJson);
}

HTTPRequest HTTPMessageBuilder::getUserProfile(std::string userId) {
	return HTTPRequest("GET", "/users/" + userId, headers, "");
}

HTTPRequest HTTPMessageBuilder::getUserList() {
	return HTTPRequest("GET", "/users", headers, "");
}

void HTTPMessageBuilder::setHeader(std::string header,
                                   std::string headerValue) {
	headers[header] = headerValue;
	if (headerValue == "") { headers.erase(header); }
}