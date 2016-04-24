//
// Created by chris on 23/04/16.
//

#ifndef APPSERVER_HTTPMESSAGE_H
#define APPSERVER_HTTPMESSAGE_H

#include <string>
#include <map>

class HTTPRequest {

	std::map<std::string, std::string> headers;
	std::string verb;
	std::string uri;
	std::string body;
	std::string message;
public:
	HTTPRequest();

	HTTPRequest(std::string verb, std::string uri,
	            std::map<std::string, std::string> headers, std::string body);

	HTTPRequest(struct http_message *hm);

	std::string getHeader(std::string header);

	std::string toString();

	std::string getVerb();;

	std::string getUri();;

	std::string getBody();;

	bool isEmpty();

	const char *toCString();
};

#endif //APPSERVER_HTTPMESSAGE_H
