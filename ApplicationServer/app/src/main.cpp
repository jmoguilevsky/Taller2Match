#include "Server.h"
#include "../mongoose-master/mongoose.h"
#include <iostream>

using namespace std;

void* function(void* data){
	// Esta función se ejecuta en otro thread. Cuando se escribe
	// "quit" en la consola, se cierra el server. PERO VALGRIND DICE QUE
	// HAY LEAKS CON LOS THREADS DE MONGOOSE, NO CON ESTE THREAD...
	std::string s;
	do {
		std::cin >> s;
	} while(s != "quit");
	Server::stop();
}

int main(void) {
//	Inicia el server en el puerto 8000.
	mg_start_thread(function,NULL);
	Server::init("8000","localhost:8080");
	return 0;
}