#include "src/Mongoose/MgServer.h"
#include "src/HandlersHTTP/MatchRequestHandler.h"
#include "src/SharedServerConnection.h"
#include "unistd.h"
#include "src/Log/Log.h"

const static std::string SHARED_SERVER = "enigmatic-depths-58073.herokuapp.com:80";
const static std::string DEFAULT_PORT = "7000";

void *checkForQuit(void *data) {

	std::cout << "type 'quit' to shutdown server" << std::endl;

	std::string input;
	do {
		std::cin >> input;
	} while (input != "quit");

	((MgServer *) data)->stop();
}

int parseArgs(int argc, char **argv, LogLevel &logLevel, std::string &port, std::string &sharedServer) {
	int c;
	while ((c = getopt(argc, argv, "hl:p:s:")) != -1)
		switch (c) {
			case 'h': {
				std::cout << "Match - Application Server" << std::endl;
				std::cout << "==========================" << std::endl;
				std::cout << "Options:\n\n";
				std::cout << "-h \t\t\tShows this info." << std::endl;
				std::cout <<
				"-l [LOG_LEVEL]\t\tSets log level. 0 => ERROR; 1 => WARNING; 2 => INFO; 3 => DEBUG." <<
				std::endl;
				std::cout << "-p [LISTEN_PORT]\tSets port for incomming connections." << std::endl;
				std::cout << "-s [SHARED_SERVER]\tSets Shared Server." << std::endl;
				std::cout << "==========================" << std::endl;
				std::cout << "By: " << std::endl;
				std::cout << "Manuel Battan" << std::endl;
				std::cout << "Jonathan Moguilevsky" << std::endl;
				std::cout << "Sebastián Elizalde" << std::endl;
				std::cout << "Christian Pedersen" << std::endl;
				exit(0);
				break;
			}
			case 'l':
				switch (atoi(optarg)) {
					case 0:
						logLevel = ERROR;
						break;
					case 1:
						logLevel = WARNING;
						break;
					case 2:
						logLevel = INFO;
						break;
					case 3:
						logLevel = DEBUG;
						break;
					default:
						std::cout << "Wrong log level: using ERROR" << std::endl;
						logLevel = ERROR;
				}
				break;
			case 'p':
				port = optarg;
				break;
			case 's':
				sharedServer = optarg;
				break;
			case '?':
				if (optopt == 'l' || optopt == 'p' || optopt == 's')
					fprintf(stderr, "Option -%c requires an argument. Using default.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr,
							"Unknown option character `\\x%x'.\n",
							optopt);
				return 1;
			default:
				abort();
		}

	for (int index = optind; index < argc; index++)
		printf("Non-option argument %s\n", argv[index]);

}

int main(int argc, char** argv) {
	opterr = 0;
	LogLevel logLevel = ERROR;
	std::string port = DEFAULT_PORT;
	std::string sharedServer = SHARED_SERVER;

	parseArgs(argc, argv, logLevel, port, sharedServer);

	Log::init("log.txt", logLevel);

	SharedServerConnection serverConnection(SHARED_SERVER);
	MatchRequestHandler matchRequestHandler(serverConnection);

	MgServer server(port, matchRequestHandler);
	std::cout << "Log level: " << logLevel << std::endl;

	Log::info("Listening connections on port " + port);
	Log::info("Shared server: " + sharedServer);

	std::cout << "MgServer started on port " << port << std::endl;
	std::cout << "Configuring shared server, trying to connect to " << sharedServer << std::endl;

	mg_start_thread(checkForQuit, &server);

	server.start();
	return 0;
}