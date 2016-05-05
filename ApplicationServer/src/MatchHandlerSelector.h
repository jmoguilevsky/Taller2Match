//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "Handlers/Handler.h"

// TODO: Eliminar estas dependencias agregando objetos que colaboren a abstraerse.
#include "DB/LoginDB.h"
#include "DB/MatchesDB.h"
#include "TokenManager.h"
#include "SharedData.h"
#include "HandlerSelector.h"
#include "DB/DBManager.h"

class MatchHandlerSelector : public HandlerSelector {
// TODO: Mandar cosas a private !

private:

	TokenManager tokenManager;

	SharedData &sharedData;

	DBManager &dbManager;

	std::map<std::string, std::map<std::string, Handler *(MatchHandlerSelector::*)(HTTPRequest &)>> constructorSelector;

	Handler *createLoginHandler(HTTPRequest &request);

	Handler *createSignUpHandler(HTTPRequest &request);

	Handler *createAuthenticationErrorHandler(HTTPRequest &request);

	Handler *createMatcherHandler(HTTPRequest &request);

public:

	MatchHandlerSelector(DBManager &dbManager, SharedData &sharedData);

	~MatchHandlerSelector();

	Handler *getRequestHandler(HTTPRequest &request);


};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
