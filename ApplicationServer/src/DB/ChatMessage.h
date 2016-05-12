//
// Created by chris on 27/04/16.
//

#ifndef APPSERVER_CHATMESSAGE_H
#define APPSERVER_CHATMESSAGE_H

#include <string>
#include <iostream>
#include "../json/json.h"
#include "../utils.h"

class ChatMessage {
	std::string time; //TODO otro tipo que no sea string!
	std::string userFrom;
	std::string userTo;
	std::string message;
	std::string read;
	Json::Value msgJson;
public:
	void fromJson(Json::Value &json) {
		Json::Value msg = json["message"];
		userFrom = msg["from"].asString();
		userTo = msg["to"].asString();
		message = msg["msg"].asString();
		read = msg["read"].asString();
		// TODO agregar timestamp
	}

	std::string getUserFrom() {
		return userFrom;
	}

	std::string getUserTo() {
		return userTo;
	}

	std::string getMsg() {
		return message;
	}

	bool isRead() {
		return read == "yes";
	}

	void setRead() {
		read = "yes";
	}

	Json::Value toJson() {
		Json::Value json;
		Json::Value msg;
		msg["from"] = userFrom;
		msg["to"] = userTo;
		msg["read"] = read;
		msg["msg"] = message;
		json["message"] = msg;
		return json;
	}

	std::string toString() {
		std::cout << "READ IS" << read;
		return utils::JsonToString(toJson());
	}

};


#endif //APPSERVER_CHATMESSAGE_H
