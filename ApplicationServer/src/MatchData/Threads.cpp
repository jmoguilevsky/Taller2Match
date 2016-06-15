//
// Created by chris on 12/06/16.
//

#include "Threads.h"

void startThread(void *(*function)(void *), void *data) {
    pthread_t thread_id = (pthread_t) 0;
    pthread_attr_t attr;

    (void) pthread_attr_init(&attr);
    (void) pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&thread_id, &attr, function, data);
    pthread_attr_destroy(&attr);
}

void *checkForQuitThread(void *data) {
    std::cout << "type 'quit' to shutdown server" << std::endl;

    std::string input;
    do {
        std::cin >> input;
    } while (input != "quit");

    ((MgServer *) data) -> stop();
}

void *pollUserThread(void *data) {
    std::pair < ConnectedUsers * , std::string > *pair = (std::pair < ConnectedUsers * , std::string > *)
    data;
    ConnectedUsers *connected = pair -> first;
    std::string userId = pair -> second;
    MgHTTPClient client;
    bool ok = client . connectToUrl(connected -> getUserUrl(userId));
    if (!ok) {
        std::cout << "LALALA";
        connected -> disconnect(userId);
        return NULL;
    }
    HTTPRequest request("GET", "/connected", "");
    HTTPResponse response = client . sendRequest(request);
    if (response . getCode() != 200) {
        connected -> disconnect(userId);
    }
    return NULL;
}

void *pollingThread(void *data) {
    // TODO Buscar la forma de cortar este thread con un flag o algo así.
    ConnectedUsers *connectedUsers = (ConnectedUsers *) data;
    while (true) {
        sleep(3000);
        std::cout << "POLLING USERS" << std::endl;
        std::vector <std::string> users = connectedUsers -> getAllUsers();
        for (int i = 0; i < users . size(); i++) {
            std::string userId = users[i];
            std::cout << "POLLING USER " << userId << std::endl;
            std::pair < ConnectedUsers * ,
                    std::string > *pair = new std::pair<ConnectedUsers *, std::string>(connectedUsers, userId);
            startThread(pollUserThread, pair);
        }
    }
}