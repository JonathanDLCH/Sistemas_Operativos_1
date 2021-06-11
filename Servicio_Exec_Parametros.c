/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Servicio Execvp
Desde linea de argumentos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	pid_t pid;

	pid=fork();
	switch(pid){
		case -1: //Error del fork
			exit(-1);
		case 0: //Hijo
			if (execvp(argv[1],&argv[1])<0)
			perror("exec");
			break;
		default: //Padre
			printf("\nProceso padre\n");
	}
	return 0;
}