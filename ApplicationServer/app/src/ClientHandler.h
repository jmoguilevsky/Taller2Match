//
// Created by chris on 15/04/16.
//

#ifndef MULTITHREADMULTICONNECTION_CLIENTHANDLER_H
#define MULTITHREADMULTICONNECTION_CLIENTHANDLER_H

#include <string>
#include <queue>
#include "../mongoose-master/mongoose.h"


class ClientHandler{
	bool waiting;

	std::queue<std::string> requestQueue; // Cola de requests a procesar. Capaz que no hace falta.
	struct mg_connection* connectionToClient; // La conexión hacia la app Android para este usuario.
	struct mg_connection* connectionToShared; // La conexión hacia el shared server para este usuario.
public:

	ClientHandler(mg_connection *connectionToClient,
	              const std::string &sharedAddress);

	void handleLastRequest(const std::string& requestAnswerFromShared);

	bool isWaiting();

	void sendNextRequest();

	void addRequest(std::string basic_string);

	void handle(mg_connection *pConnection, int i);

	static void sharedHandler(mg_connection *connectionToShared, int ev, void *p);

private:
	std::string getRequestToShared(const std::string &originalRequest);


};


#endif //MULTITHREADMULTICONNECTION_CLIENTHANDLER_H