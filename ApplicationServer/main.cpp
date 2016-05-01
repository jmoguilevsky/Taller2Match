#include "src/Server.h"

const static std::string SHAREDSERVER = "enigmatic-depths-58073.herokuapp.com:80";
const static std::string DEFAULTPORT = "7000";

void *checkForQuit(void *data) {

	std::cout << "type 'quit' to shutdown server" << std::endl;

	std::string input;
	do {
		std::cin >> input;
	} while (input != "quit");

	((Server *) data)->stop();
}

int main(int argc, char** argv) {

	std::string sharedServer;
	std::string port;

	if (argc < 3) {
		sharedServer = SHAREDSERVER;
		port = DEFAULTPORT;
	} else {
		port = argv[1];
		sharedServer = argv[2];
	}

	Server server(port, sharedServer);

	std::cout << "Server started on port " << port << std::endl;
	std::cout << "Configuring shared server, trying to connect to " << sharedServer << std::endl;

	mg_start_thread(checkForQuit, &server);

	server.start();
	return 0;
}