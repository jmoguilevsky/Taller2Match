//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_REQUESTHANDLER_H
#define APPSERVER_REQUESTHANDLER_H

#include "../HTTPRequest.h"
#include "../DB/DBManager.h"
#include "../HTTPResponse.h"

class RequestHandler {
private:
	HTTPRequest request;
	HTTPResponse *response;

public:

	/*HTTPRequest request(hm);
	HTTPRequest reqToShared = server.getRequestToShared(request);
	ConnectionToShared connectionToShared(server.sharedAddress);
	HTTPRequest responseShared = connectionToShared.sendRequest(
			reqToShared);
	std::cout << "Response:\n" << responseShared.toString() << std::endl;*/
	virtual HTTPResponse handle() = 0;
};

#endif //APPSERVER_REQUESTHANDLER_H
