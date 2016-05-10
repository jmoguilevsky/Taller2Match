#include "Semaforo.h"

Semaforo::inicializar() {
	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->valorInicial;
	int resultado = semctl(this->id, 0, SETVAL, init);
	return resultado;
}

Semaforo::Semaforo(char* nombre, int valorInicial) {
	this->valorInicial = valorInicial;
	key_t key = ftok(nombre, 'M');
	this->id = semget(clave, 1, 0666|IPC_CREAT);

	this->inicializar();
}

Semaforo::~Semaforo() { }

int Semaforo::v() {
	struct sembuf operacion; 
	operacion.sem_num = 0;
	operacion.sem_op = 1;
	operacion.sem_flg = SEM_UNDO;
	
	int resultado = semop(this->id, &operacion, 1);
	return resultado;
}

int Semaforo::p() {
	struct sembuf operacion; 
	operacion.sem_num = 0;
	operacion.sem_op = -1;
	operacion.sem_flg = SEM_UNDO;
	
	int resultado = semop(this->id, &operacion, 1);
	return resultado;
}

void Semaforo::eliminar() {
	semctl(this->id, 0, IPC_RMID);
}


