/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Servicio Execlp
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int status;

	pid=fork();
	switch(pid){
		case -1: //Error del fork
			exit(-1);
		case 0: //Hijo
			//execlp("ls","ls","-l",NULL);
			execlp("/home/jonathan/Escritorio/Hijo","/home/jonathan/Escritorio/Hijo","5","5",NULL);
			perror("exec");
			break;
		default: //Padre
			printf("\nProceso padre\n");
	}
	return 0;
}