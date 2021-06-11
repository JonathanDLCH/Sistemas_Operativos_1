/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Proceso Wait: Pares e Impares
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>

int main ()
{
	pid_t pid;
	int status;

	pid=fork();

	if (pid>0)
	{
		wait(&status);
		printf("\nID_padre: %d",getpid());
		if (WIFEXITED(status))
		{
			printf("\nStatus de hijo: %d",WEXITSTATUS(status));
		}
	}
	if (pid==0)
	{
		printf("\nID_padre: %d",getppid());
		printf("\nID_Hijo: %d",getpid());
		return 10;
	}
}