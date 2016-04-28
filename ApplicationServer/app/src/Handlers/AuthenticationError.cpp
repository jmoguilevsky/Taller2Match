//
// Created by chris on 27/04/16.
//

#include "AuthenticationError.h"

AuthenticationError::AuthenticationError(const HTTPRequest &request)
		: RequestHandler(
		request) { }

HTTPResponse AuthenticationError::handle() {
	std::map<std::string, std::string> headers;
	return HTTPResponse("401", "Unauthorized", headers, request.getBody());
}