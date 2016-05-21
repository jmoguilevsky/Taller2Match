#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {
private:
	int id;
	int valorInicial;
	int inicializar();
	
public:
	Semaforo(char* nombre, int valorInicial);
	virtual ~Semaforo();	
	int p();
	int v();
	void eliminar();
};

#endif
