//
// Created by chris on 23/04/16.
//

#include <fstream>
#include "../Mongoose/MgHTTPClient.h"
#include "../Mongoose/MgServer.h"
#include "../Exceptions/ParseException.h"

#define CRLF "\r\n"
#define HTTP_VERSION "HTTP/1.1"


HTTPRequest::HTTPRequest(std::string verb, std::string uri,
                         std::map<std::string, std::string> headers,
                         std::string body) {
	// TODO poner métodos para ver los headers!
	this->verb = verb;
	this->uri = uri;
	this->body = body;
	this->message = verb + " " + uri + " " + HTTP_VERSION + CRLF;
	for (std::map<std::string, std::string>::iterator it = headers.begin();
	     it != headers.end(); ++it) {
		this->message += it->first + ":" + it->second + CRLF;
	}

	std::stringstream s;
	s << body.size();
	std::string t;
	s >> t;

	if(verb == "POST" || verb == "PUT")this->message += "Content-Length:" + t + CRLF;
	if (body != "")this->message += CRLF + body;
	this->message += CRLF;
}

HTTPRequest::HTTPRequest(struct http_message *hm) {
	//TODO ver cómo separar los headers acá
	verb = std::string(hm->method.p, hm->method.len);
	uri = std::string(hm->uri.p, hm->uri.len);
	body = std::string(hm->body.p, hm->body.len);
	for (int i = 0; i < MG_MAX_HTTP_HEADERS; i++) {
		headers[util::mgStrToString(
				hm->header_names[i])] = util::mgStrToString(
				hm->header_values[i]);
	}
	message = std::string(hm->message.p, hm->message.len);

}

std::string HTTPRequest::toString() {
	// Devuelve todo como string, tal como se envía y se recibe el mensaje.
	return message;
}

const char *HTTPRequest::toCString() {
	return message.c_str();
}

std::string HTTPRequest::getVerb() {
	return verb;
}

std::string HTTPRequest::getUri() {
	return uri;
}

std::string HTTPRequest::getBody() {
	return body;
}

bool HTTPRequest::isEmpty() {
	// TODO DUDOSO....
	return (verb == "") && (uri == "") && (body == "");
}

HTTPRequest::HTTPRequest() {
	//std::cout << "this has been called" << std::endl;
}

std::string HTTPRequest::getHeader(std::string header) {
	if (headers.count(header) == 0) throw ParseException ("Missing header: \"Authorization\"");
	return headers[header];
}

HTTPRequest::HTTPRequest(std::string verb, std::string uri, std::string body) {
	this->verb = verb;
	this->uri = uri;
	this->body = body;
	this->message = verb + " " + uri + " " + HTTP_VERSION + CRLF;
	if (body != "")this->message += CRLF + body + CRLF;
	this->message += CRLF;
}


std::vector<std::string> HTTPRequest::getSplitUri() {
	std::vector<std::string> elems;
	util::split(uri, '/', elems);
	elems.erase(elems.begin());
	return elems;
}