//
// Created by chris on 12/05/16.
//

#include "HTTP.h"

HTTPResponse HTTP::BadRequest() {
	std::map<std::string, std::string> headers;
	return HTTPResponse("400", "Bad Request", headers, "");
}

HTTPResponse HTTP::Unauthorized() {
	std::map<std::string, std::string> headers;
	return HTTPResponse("409", "Unauthorized", headers, "");
}

HTTPResponse HTTP::OK(std::string str) {
	std::map<std::string, std::string> headers;
	return HTTPResponse("200", "OK", headers, str);
}

HTTPResponse HTTP::Error(std::string msg) {
	std::map<std::string, std::string> headers;
	return HTTPResponse("400", "Error", headers, msg);
}

HTTPResponse HTTP::OKJson(std::string json) {
	std::map<std::string, std::string> headers;
	headers["Content-type"] = "application/json";
	return HTTPResponse("200", "OK", headers, json);
}