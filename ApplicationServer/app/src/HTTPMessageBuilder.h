//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_HTTPMESSAGEBUILDER_H
#define APPSERVER_HTTPMESSAGEBUILDER_H

#include "HTTPRequest.h"

class HTTPMessageBuilder {
private:
	HTTPMessageBuilder();

	static std::map<std::string, std::string> headers;
public:
	// TODO los headers necesarios para cada request sería mejor ponerlos en cada función específica.
	// TODO si es que no son siempre los mismos
	static void setHeader(std::string header, std::string headerValue);

	static HTTPRequest getUserList();

	static HTTPRequest getUserProfile(std::string userId);

	static HTTPRequest getModifyUserProfile(std::string userId,
	                                        std::string userProfileJson);

	static HTTPRequest getChangeProfilePhoto(std::string userId,
	                                         std::string photoJson);

	static HTTPRequest getDeleteUser(std::string userId);

	static HTTPRequest getInterestList();

	static HTTPRequest getNewInterest(std::string interestJson);
};

#endif //APPSERVER_HTTPMESSAGEBUILDER_H
