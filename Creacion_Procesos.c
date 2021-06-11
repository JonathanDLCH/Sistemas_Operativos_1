/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Creacion de Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int x=5,y=10,z=20;
	pid=fork(); //Creamos un proceso hijo

	if(pid>0){ //Padre
		x=x+100;
		y=y+200;
		printf("\nPadre-pid:%d \n X=%d,Y=%d, Z=%d\n",getpid(),x,y,z);
	}
	if(pid==0){ //Hijo
		x=x+150;
		y=y+250;
		printf("\nHijo-pid:%d \n X=%d,Y=%d, Z=%d\n",getpid(),x,y,z);
	}

	printf("Z=%d",z );
	return 0;
}