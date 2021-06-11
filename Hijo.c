/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Recibe n= numero de tiempo para dormir un proceso
Recibe m= numero de veces que imprime el id del proceso
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	sleep(atoi(argv[1]));
	pid=fork();
	for (int i=0; i<atoi(argv[2]); i++)
	{
		switch(pid){
			case -1: exit(-1); break;
			case 0: printf("\nID-Hijo: %d",getpid()); break;
			default: printf("\nID-Padre: %d",getppid());
		}
	}
	return 0;
}