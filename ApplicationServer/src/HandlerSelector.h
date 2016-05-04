//
// Created by mvbattan on 04/05/16.
//

#ifndef APPLICATIONSERVER_HANDLERSELECTOR_H
#define APPLICATIONSERVER_HANDLERSELECTOR_H

#include <map>
#include "Handlers/RequestHandler.h"

// TODO: Eliminar estas dependencias agregando objetos que colaboren a abstraerse.
#include "DB/LoginDB.h"
#include "DB/MatchesDB.h"
#include "TokenManager.h"
#include "SharedServerConnection.h"

class HandlerSelector;

typedef RequestHandler*(*HandlerConstructor)(HTTPRequest&, HandlerSelector*);

class HandlerSelector {
// TODO: Mandar cosas a private !
public:
    std::map<std::string, std::map<std::string, HandlerConstructor>> constructorSelector;
    LoginDB db;
    MatchesDB matchesDB;
    TokenManager tokenManager;
    SharedServerConnection sharedServer;

    HandlerSelector(std::string sharedConnectionString);
    ~HandlerSelector();
    RequestHandler* getRequestHandler(HTTPRequest& request);
};

#endif //APPLICATIONSERVER_HANDLERSELECTOR_H
