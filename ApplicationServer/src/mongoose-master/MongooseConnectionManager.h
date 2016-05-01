#ifndef APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
#define APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
#include "mongoose.h"
#include "../Server.h"

class MongooseConnectionManager {
public:
    MongooseConnectionManager();
    ~MongooseConnectionManager();
    void initManager();
    void configureConnection(std::string port);
    void deleteManager();
    void checkForRequests(int everyMilliseconds);

private:
    struct mg_mgr mgr;
    struct mg_connection *listeningConnection;
};


#endif //APPLICATIONSERVER_MOONGOSECONNECTIONMANAGER_H
