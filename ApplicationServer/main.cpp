#include "src/Server.h"

using namespace std;

void *checkForQuit(void *data) {
	// Esta función se ejecuta en otro thread. Cuando se escribe
	// "quit" en la consola, se cierra el server.
	std::string s;
	do {
		std::cin >> s;
	} while (s != "quit");

	((Server *) data)->stop();
}

int main(void) {
//	Inicia el server en el puerto 8000.

	// Esto podría estar dentro de Server, da lo mismo.
	Server server("7000", "enigmatic-depths-58073.herokuapp.com:80");
	std::cout << "Server started" << std::endl;
	mg_start_thread(checkForQuit, &server);
	server.start();
	return 0;
}