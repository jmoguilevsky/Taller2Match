//
// Created by chris on 24/04/16.
//


#include <map>
#include "HTTPResponse.h"
#include "../Mongoose/mongoose-master/mongoose.h"
#include "../util.h"

#define CRLF "\r\n"

HTTPResponse::HTTPResponse(std::string code, std::string phrase,
                           std::map<std::string, std::string> headers,
                           std::string body) {
	message = HTTP_VERSION;
	message += " " + code + " " + phrase + CRLF;
	for (std::map<std::string, std::string>::iterator it = headers.begin();
	     it != headers.end(); ++it) {
		message += it->first + ":" + it->second + CRLF;
	}
	if (body != "") message += CRLF + body + CRLF;
	message += CRLF;
}

const char *HTTPResponse::toCString() {
	return message.c_str();
}

HTTPResponse::HTTPResponse() {

}

std::string HTTPResponse::toString() {
	return "";
}

HTTPResponse::HTTPResponse(struct http_message *hm) {
	// Parsear el mensaje
	this->code = hm->resp_code;
	this->body = util::mgStrToString(hm->body);
}

std::string HTTPResponse::getBody() {
	return body;
}

int HTTPResponse::getCode() {
	return code;
}










