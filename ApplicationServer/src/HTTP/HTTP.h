//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_HTTP_H
#define APPSERVER_HTTP_H

#include "HTTPResponse.h"

// Wrapper para obtener las HTTPResponse más fácilmente.

namespace HTTP {

	HTTPResponse OK(std::string str = "");

	HTTPResponse OKJson(std::string json);

	HTTPResponse NotFound();

	HTTPResponse Error(std::string msg = "");

	HTTPResponse BadRequest();

	HTTPResponse Unauthorized();
};


#endif //APPSERVER_HTTP_H
