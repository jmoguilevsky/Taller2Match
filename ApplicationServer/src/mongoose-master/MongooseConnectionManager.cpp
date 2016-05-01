#include "MongooseConnectionManager.h"

void MongooseConnectionManager::initManager() {
    mg_mgr_init(&mgr, NULL);
}

void MongooseConnectionManager::configureConnection(std::string port, Server* server) {
    struct mg_bind_opts opts;
    opts.user_data = (void *) server;
    listeningConnection = mg_bind_opt(&mgr, port.c_str(), server.clientHandler, opts);
    mg_enable_multithreading(listeningConnection);
    mg_set_protocol_http_websocket(listeningConnection);
}

void MongooseConnectionManager::checkForRequests(int everyMilliseconds) {
    mg_mgr_poll(&mgr, everyMilliseconds);
}

void MongooseConnectionManager::deleteManager() {
    mg_mgr_free(&mgr);
}

