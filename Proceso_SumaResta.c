/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Prosesos Operacion e ID
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int a=2,b=3;
	pid_t pid_1,pid_2;

	pid_1=fork(); //Creamos un proceso hijo

	if(pid_1>0){ //Padre
		printf("\nId pid_1 padre: %d",getpid());
		printf("\nId padre pid_1 padre: %d",getppid());
	}
	if(pid_1==0){ //Hijo
		pid_2=fork();
		if(pid_2>0){
			printf("\n%d+%d=%d",a,b,(a+b));
			printf("\nId pid_2 padre: %d",getpid());
			printf("\nId pid_1 hijo: %d",getppid());
		}
		if(pid_2==0){
			printf("\n%d-%d=%d",a,b,(a-b));
			printf("\nId pid_2 hijo: %d",getpid());
			printf("\nId pid_1 hijo: %d",getppid());
		}
	}

	return 0;
}