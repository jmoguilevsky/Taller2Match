#include "Server.h"
#include "../mongoose-master/mongoose.h"
#include "DBManager.h"
#include <iostream>
#include <map>

using namespace std;

void* checkForQuit(void* data){
	// Esta función se ejecuta en otro thread. Cuando se escribe
	// "quit" en la consola, se cierra el server. PERO VALGRIND DICE QUE
	// HAY LEAKS CON LOS THREADS DE MONGOOSE, NO CON ESTE THREAD...
	std::string s;
	do {
		std::cin >> s;
	} while(s != "quit");
	Server::stop();
	DBManager::closeDBs();
}

int main(void) {
//	Inicia el server en el puerto 8000.
	mg_start_thread(checkForQuit,NULL);
	// Esto podría estar dentro de Server, da lo mismo.
	DBManager::initDBs("likes","matches","noMatches");
	Server::init("8000","localhost:8080");
	return 0;
}