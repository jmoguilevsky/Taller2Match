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
//! Inicia la función recibida por parámetro en un nuevo thread.
void startThread(void *(*function)(void *), void *data);
//! Función que espera a que se ingrese por consola "quit" para cerrar el servidor.
void *checkForQuitThread(void *data);

#endif //APPSERVER_POLLINGTHREAD_H
