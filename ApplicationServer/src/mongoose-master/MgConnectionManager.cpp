#include "MgServer.h"
#include "MgHTTPClient.h"

MgConnectionManager::MgConnectionManager() {
	mg_mgr_init(&mgr, NULL);
}

MgConnectionManager::~MgConnectionManager() {
	mg_mgr_free(&mgr);
}

mg_connection *MgConnectionManager::configureListeningConnection(std::string port, void *data,
                                                                 mg_event_handler_t eventHandler) {
	mg_bind_opts opts;
	opts.user_data = data;
	mg_connection *listeningConnection = mg_bind_opt(&mgr, port.c_str(), eventHandler, opts);
	mg_enable_multithreading(listeningConnection);
	mg_set_protocol_http_websocket(listeningConnection);
	return listeningConnection;
}

mg_connection *MgConnectionManager::configureOutboundConnection(std::string url, void *data,
                                                                mg_event_handler_t eventHandler) {
	mg_connection *outboundConnection = mg_connect(&mgr, url.c_str(), eventHandler);
	outboundConnection->user_data = data;
	mg_set_protocol_http_websocket(outboundConnection);
	return outboundConnection;
}


void MgConnectionManager::poll(int everyMilliseconds) {
	mg_mgr_poll(&mgr, everyMilliseconds);
}