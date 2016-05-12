//
// Created by chris on 23/04/16.
//

#ifndef APPSERVER_HTTPMESSAGE_H
#define APPSERVER_HTTPMESSAGE_H

#include <string>
#include <map>

//! Request HTTP.

class HTTPRequest {

	std::map<std::string, std::string> headers;
	std::string verb;
	std::string uri;
	std::string body;
	std::string message;
public:
	HTTPRequest();

	//! Crea el HTTPRequest dado un HTTP verb, una URI, un map con headers del tipo {header,value}, y un body.
	HTTPRequest(std::string verb, std::string uri,
	            std::map<std::string, std::string> headers, std::string body);

	HTTPRequest(std::string verb, std::string uri, std::string body);


	//! Crea un HTTPRequest dado un http_message de Mongoose.
	HTTPRequest(struct http_message *hm);

	//! Devuelve el valor que tiene el header especificado para este request.
	std::string getHeader(std::string header);

	//! Devuelve el HTTPRequest completo como un std::string.
	std::string toString();

	//! Devuelve el HTTP verb.
	std::string getVerb();;

	//! Devuelve la URI HTTP.
	std::string getUri();;

	//! Devuelve el body del request HTTP.
	std::string getBody();;

	//! Devuelve true si es un request vacío, false si no.
	bool isEmpty();

	//! Devuelve el HTTPRequest completo como un char* de C.
	const char *toCString();
};

#endif //APPSERVER_HTTPMESSAGE_H
