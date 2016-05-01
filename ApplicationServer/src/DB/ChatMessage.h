//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_CHATMESSAGE_H
#define APPSERVER_CHATMESSAGE_H

#include <string>
#include "../json/json.h"

class ChatMessage {
	std::string time; //TODO otro tipo que no sea string!
	std::string userFrom;
	std::string userTo;
	std::string message;
	Json::Value msgJson;
public:
	ChatMessage(Json::Value &msgJson);
};


#endif //APPSERVER_CHATMESSAGE_H
