//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_HTTP_H
#define APPSERVER_HTTP_H

#include "HTTPResponse.h"
#include "../json/json.h"

// Wrapper para obtener las HTTPResponse más fácilmente.

namespace HTTP {
	//! Devuelve una response HTTP: "HTTP/1.1 200 OK".
	HTTPResponse OK(std::string str = "");

	//! Devuelve una response HTTP: "HTTP/1.1 200 OK", con el Json en el body.
	HTTPResponse OK(Json::Value json);

	//! Devuelve una response HTTP: "HTTP/1.1 404 Not Found".
	HTTPResponse NotFound();

	//! Devuelve una response HTTP: "HTTP/1.1 400 Error".
	HTTPResponse Error(std::string msg = "");

	//! Devuelve una response HTTP: "HTTP/1.1 400 Bad Request".
	HTTPResponse BadRequest();

	//! Devuelve una response HTTP: "HTTP/1.1 409 Unauthorized".
	HTTPResponse Unauthorized();
};


#endif //APPSERVER_HTTP_H
