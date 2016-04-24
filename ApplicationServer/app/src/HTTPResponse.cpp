//
// Created by chris on 24/04/16.
//


#include <map>
#include "HTTPResponse.h"

#define CRLF "\r\n"

HTTPResponse::HTTPResponse(std::string code, std::string phrase,
                           std::map<std::string, std::string> headers,
                           std::string body) {
	message = code + " " + HTTP_VERSION + " " + phrase + CRLF;
	for (std::map<std::string, std::string>::iterator it = headers.begin();
	     it != headers.end(); ++i) {
		message += it->first + ":" + it->second + CRLF;
	}
	if (body != "") message += CRLF + body + CRLF;
	message += CRLF;
}

const char *HTTPResponse::toCString() {
	return message.c_str();
}



