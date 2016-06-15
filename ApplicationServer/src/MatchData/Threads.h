//
// Created by chris on 12/06/16.
//

#ifndef APPSERVER_POLLINGTHREAD_H
#define APPSERVER_POLLINGTHREAD_H

#include "ConnectedUsers.h"
#include <string>
#include <map>
#include <unistd.h>
#include "../Mongoose/MgHTTPClient.h"
#include "../Mongoose/MgServer.h"

void startThread(void *(*function)(void *), void *data);

void *checkForQuitThread(void *data);

void *pollUserThread(void *data);

void *pollingThread(void *data);

#endif //APPSERVER_POLLINGTHREAD_H
