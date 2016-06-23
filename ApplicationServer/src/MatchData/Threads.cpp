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
