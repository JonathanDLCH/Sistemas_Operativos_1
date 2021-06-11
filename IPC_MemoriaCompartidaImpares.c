/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Suma Impares
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define rango 100 //Rango para numeros aleatorios

int main(int argc, char *argv[]){

	key_t key;
	key=ftok("/home/jonathan/Escritorio/",'b');
	int n=atoi(argv[1]),idseg,*ptr,nimp;
	int vectorimpares[n];
	time_t t;
	srand((unsigned) time(&t));

	for (int i = 0; i < n; i++){//llenado del vector
		do{
			nimp=rand()%rango;
			vectorimpares[i]=nimp;
		}while((nimp)%2==0); //mientras este numero es par
	}

	idseg=shmget(key,sizeof(vectorimpares),IPC_CREAT | 0777);
	ptr=(int*)shmat(idseg,0,0);

	for (int i = 0; i<n; i++){
		ptr[i]=vectorimpares[i];
		printf("%d\n",ptr[i]);
	}

	return 0;
}