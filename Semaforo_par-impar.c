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
#include <sys/sem.h>

void down(int idsem,int numSem);
void up(int idsem,int numSem);
void GenerarPares(int idsem,int idshm,int *pointer,int Rep);
void GenerarImpares(int idsem,int idshm,int *pointer,int Rep);
void ConsumirNumeros(int idsem,int idshm,int *pointer,int Rep);
int par=0,impar=1;

int main(int argc, char *argv[]){
	
	key_t keyshm=ftok(".",'a'),keysmp=ftok(".",'b');
	int idshm,idsem,*pointer,Rep=50;

	int pid1,pid2;

	//Memoria utilizada como mecanismo de comunicacion entre los procesos
	idshm=shmget(keyshm,sizeof(int)*20,IPC_CREAT|0777);
	idsem=semget(keysmp,3,IPC_CREAT|0777);
	semctl(idsem,0,SETVAL,1);
	semctl(idsem,1,SETVAL,0);
	semctl(idsem,2,SETVAL,0);

	switch(pid1=fork()){
		case -1:
				perror("Error al crear al proceso.");
				shmdt(pointer);
				shmctl(idshm,IPC_RMID,NULL);
				semctl(idsem,0,IPC_RMID,0);
				exit(-1);
				break;
		case 0:
				GenerarPares(idsem,idshm,pointer,Rep);
				break;
		default:
				switch((pid2=fork())){
					case -1:
							perror("Error al crear el proceso.");
							shmdt(pointer);
							shmctl(idshm,IPC_RMID,NULL);
							semctl(idsem,0,IPC_RMID,0);
							kill(pid1,SIGKILL);
							exit(-1);
							break;
					case 0:
							ConsumirNumeros(idsem,idshm,pointer,Rep);

							shmdt(pointer);
							shmctl(idshm,IPC_RMID,NULL);
							exit(0);
							break;
					default:
							GenerarImpares(idsem,idshm,pointer,Rep);
				}
	}
	
	return 0;
}

void GenerarPares(int idsem,int idshm,int *pointer,int Rep){

	for(int i=0;i<Rep;i++){
		pointer=(int*)shmat(idshm,0,0);

		down(idsem,0);
		for (int n=0; n<5; n++){
			pointer[n]=par;
			//printf("pointer[%d]=%d\n",n,pointer[n] );
			par= par+2;
		}
		up(idsem,1);
	}
}

void GenerarImpares(int idsem,int idshm,int *pointer,int Rep){

	for(int i=0;i<Rep;i++){
		pointer=(int*)shmat(idshm,0,0);

		down(idsem,1);
		for(int n=5; n<10;n++){			
			pointer[n]=impar;
			//printf("pointer[%d]=%d\n",n,pointer[n] );
			impar= impar+2;
		}
		up(idsem,2);
	}
}

void ConsumirNumeros(int idsem,int idshm,int *pointer,int Rep){
	int cont=Rep;

	while(cont>0){
		pointer=(int*)shmat(idshm,0,0);

		down(idsem,2);
		for(int i=0;i<10 ;i++){
			printf("%d\n",pointer[i]);
		}
		cont=cont-10;
		up(idsem,0);
	}
}

void down(int idsem,int numSem){
	struct sembuf v;
	v.sem_num=numSem;
	v.sem_op=-1;
	v.sem_flg=0;

	semop(idsem,&v,1);
}

void up(int idsem,int numSem){
	struct sembuf v;
	v.sem_num=numSem;
	v.sem_op=1;
	v.sem_flg=0;

	semop(idsem,&v,1);
}