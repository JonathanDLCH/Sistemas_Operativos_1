/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Suma Pares
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

	key_t key=ftok("/home/jonathan/Escritorio/",'a'); //Obtenemos la clave
	int n=atoi(argv[1]),idseg,*ptr,npar;
	int vectorpares[n];
	time_t t;
	srand((unsigned) time(&t));

	for (int i = 0; i < n; i++){ //llenado del vector
		do{
			npar=rand()%rango;
			vectorpares[i]=npar;
		}while((npar)%2!=0); //mientras este numero no es par
	}

	idseg=shmget(key,sizeof(3*sizeof(vectorpares)),IPC_CREAT | 0777);
	ptr=(int*)shmat(idseg,0,0);

	for (int i = 0; i<n; i++){ //Escribiendo el vector en la memoria compartida
		ptr[i]=vectorpares[i];
		printf("%d\n",ptr[i]);
	}

	return 0;
}