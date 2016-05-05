#include "src/Server.h"
#include "src/DB/DBManager.h"
#include "src/MatchHandlerSelector.h"
#include "src/SharedServerConnection.h"

const static std::string SHARED_SERVER = "enigmatic-depths-58073.herokuapp.com:80";
const static std::string DEFAULT_PORT = "7000";

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
		sharedServer = SHARED_SERVER;
		port = DEFAULT_PORT;
	} else {
		port = argv[1];
		sharedServer = argv[2];
	}

	SharedServerConnection serverConnection(SHARED_SERVER);
	DBManager dbManager("login","likes","matches","noMatches");
	MatchHandlerSelector handlerSelector(dbManager,serverConnection);

	Server server(port, handlerSelector);

	std::cout << "Server started on port " << port << std::endl;
	std::cout << "Configuring shared server, trying to connect to " << sharedServer << std::endl;

	mg_start_thread(checkForQuit, &server);

	server.start();
	return 0;
}