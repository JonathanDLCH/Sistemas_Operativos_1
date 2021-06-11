/*
Benemerita Universidad Autonoma de Puebla
Jonathan De La Cruz Huerta

Sincronizacion de procesos
Escribir 5 numeros continuos usando Semaforos y Memoria compartida.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void down(int sem_id,int numSem);
void up(int sem_id,int numSem);
int producir();
void consumir(int i);
int i=1;

int main(int argc, char *argv[]){
	pid_t pid;
	int Input=0,Output=0,n=atoi(argv[1]);
	key_t keySemaphore=ftok(".",'d'),keyShmemory=ftok(".",'e');

	int sem_id=semget(keySemaphore,3,IPC_CREAT|0777); //Creamos los semaforos
	int *ptr,shm_id=shmget(keyShmemory,sizeof(int)*n,IPC_CREAT|0777); //Creamos la memoria compartida
	
	if(sem_id==-1 || shm_id==-1){ //Verificacion de la creacion del semaforo
		perror("Error: ");
		exit(-1);
	}
	semctl(sem_id,0,SETVAL,0); //Elements
	semctl(sem_id,1,SETVAL,n); //Spaces
	semctl(sem_id,2,SETVAL,1); //Em
	ptr=(int*)shmat(shm_id,0,0);

	pid=fork();
	if(pid>0){
		while(1){
			down(sem_id,1);
			down(sem_id,2);
			ptr[Input]=producir();
			Input=(Input+1)%n;
			up(sem_id,2);
			up(sem_id,0);
		}
	}
	if(pid==0){
		while(1){
			down(sem_id,0);
			down(sem_id,2);
			i=ptr[Output];
			Output=(Output+1)%n;
			up(sem_id,2);
			up(sem_id,1);
			consumir(i);
		}
	}else{
		perror("Error:");
		exit(-1);
	}

	
	return 0;
}

void down(int sem_id,int numSem){
	struct sembuf v;
	v.sem_num=numSem;
	v.sem_op=-1;
	v.sem_flg=0;

	semop(sem_id,&v,1);
}

void up(int sem_id,int numSem){
	struct sembuf v;
	v.sem_num=numSem;
	v.sem_op=1;
	v.sem_flg=0;

	semop(sem_id,&v,1);
}

int producir(){
	i++;;
	printf("Productor: %d\n",i );
	return i;
}

void consumir(int i){
	sleep(1);
	printf("Consumidor: %d\n",i);
}