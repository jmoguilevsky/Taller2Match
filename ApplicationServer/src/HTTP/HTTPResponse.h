//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_HTTPRESPONSE_H
#define APPSERVER_HTTPRESPONSE_H

#include <string>
#include <map>

#define HTTP_VERSION "HTTP/1.1"

//! Una respuesta HTTP.
class HTTPResponse {
	std::string message;
	std::string body;
public:
	//! Crea un HTTPResponse a partir de un código, la phrase HTTP (OK, Error, etc.), un map de headers (como en el HTTPRequest), y un body.
	HTTPResponse(std::string code, std::string phrase,
	             std::map<std::string, std::string> headers, std::string body);

	//! Devuelve el HTTPResponse completo como un char* de C.
	HTTPResponse();

	HTTPResponse(struct http_message *hm);
	const char *toCString();

	std::string toString();

	std::string getBody();

	int getCode();

	int code;
};


#endif //APPSERVER_HTTPRESPONSE_H
