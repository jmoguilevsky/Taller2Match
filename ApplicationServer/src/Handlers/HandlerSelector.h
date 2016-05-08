//
// Created by chris on 04/05/16.
//

#ifndef APPSERVER_HANDLERSELECTOR_H
#define APPSERVER_HANDLERSELECTOR_H


#include "Handler.h"

// Para que el MgServer pueda usarse para cualquier cosa.
class HandlerSelector {

public:
	virtual Handler* getRequestHandler(HTTPRequest& request) = 0;
};


#endif //APPSERVER_HANDLERSELECTOR_H
