//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_HTTPRESPONSE_H
#define APPSERVER_HTTPRESPONSE_H

#include <string>
#include <map>

#define HTTP_VERSION "HTTP/1.1"

class HTTPResponse {
	std::string message;
public:
	HTTPResponse(std::string code, std::string phrase,
	             std::map<std::string, std::string> headers, std::string body);

	const char *toCString();
};


#endif //APPSERVER_HTTPRESPONSE_H
