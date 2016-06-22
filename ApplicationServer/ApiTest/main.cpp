#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include "Semaforo.h"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char** argv) {
	
	int pipe_fd[2];
	pipe(pipe_fd);

	pid_t id = fork();
	if (id == 0) {
		// Levantamos el server
		close(pipe_fd[ESCRITURA]);
		dup2(pipe_fd[LECTURA], STDIN_FILENO);
		char* args;
		execv("app", &args);
		close(pipe_fd[LECTURA]);
		exit(0);

	} else {
		sleep(3);
		
		close(pipe_fd[LECTURA]);
		id = fork();
 
		if (id == 0) {
			system("./ApiTest/curlRequests.py");
			exit(0);
		} else {
			dup2(pipe_fd[ESCRITURA], STDOUT_FILENO);
			waitpid(id, NULL, 0);
			std::cout << "quit" << std::endl;
			close(pipe_fd[ESCRITURA]);
		}
	}
	
	wait(NULL);

	return 0;
}
