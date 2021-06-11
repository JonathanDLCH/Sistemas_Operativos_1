/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Proceso Wait: 10 numeros
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>

#define size 10
void main ()
{
	pid_t pid_1;
	int n, fd1, fd2, count, status;
	time_t t;

	srand((unsigned) time(&t));	//numeros aleatorios en cada compilacion
	pid_1 = fork();

	if(pid_1 == 0)
	{
		fd1 = creat("datos1.dat", 0777);
		fd1 = open("datos1.dat", 1);
		for(count = 0; count < size; count++)
		{
			do{
				n = rand() % 100;
			}while( n % 2 != 0);
			write(fd1, &n, sizeof(int));
		}
	}
	
	if(pid_1 > 0){
		wait(&status);
		fd1 = open("datos1.dat", 0);
		for(count = 0; count < size; count++)
		{
			read(fd1, &n, sizeof(int));
			printf("\n %d", n);
		}
	}
}