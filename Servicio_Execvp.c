/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Servicio Execvp
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	char *argumentos[4];
	argumentos[0]="/home/jonathan/Escritorio/Hijo";
	argumentos[1]="5";
	argumentos[2]="5";
	argumentos[3]=NULL;

	pid=fork();
	switch(pid){
		case -1: //Error del fork
			exit(-1);
		case 0: //Hijo
			execvp(argumentos[0],argumentos);
			perror("exec");
			break;
		default: //Padre
			printf("\nProceso padre\n");
	}
	return 0;
}