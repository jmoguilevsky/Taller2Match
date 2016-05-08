//
// Created by chris on 27/04/16.
//

#include "AuthenticationError.h"
#include "../DB/NoSQLDatabase.h"

AuthenticationError::AuthenticationError(const HTTPRequest &request)
		: Handler(
		request) { }

HTTPResponse AuthenticationError::handle() {
	std::map<std::string, std::string> headers;
	return HTTPResponse("401", "Unauthorized", headers, request.getBody());
}