//
// Created by chris on 06/05/16.
//

#ifndef APPSERVER_NOTIFICATION_H
#define APPSERVER_NOTIFICATION_H

#include <string>

#define NOTIF_NEW_MSG 1
#define NOTIF_NEW_MATCH 2

class Notification {
	int type;

public:
	bool set(int type, std::string content) {

	}

	int getType() {
		return type;
	}
};


#endif //APPSERVER_NOTIFICATION_H
