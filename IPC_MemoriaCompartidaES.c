/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Entrada y salida
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	pid_t pid;
	key_t key;
	key=ftok("/home/jonathan/Escritorio/",'a');
	int idseg,*pointer,x;
	pid=fork();
	if(pid>0){
		idseg=shmget(key,sizeof(int),IPC_CREAT | 0777); // | 0777
		pointer=(int*)shmat(idseg,0,0);
		*pointer=5;
	}
	if (pid==0){
		sleep(2);
		idseg=shmget(key,sizeof(int),IPC_CREAT | 0777);
		pointer=(int*)shmat(idseg,0,0);
		x=*pointer;
		printf("\n%d",x);

		shmdt(pointer);
		shmctl(idseg,IPC_RMID,NULL);
	}
	
	return 0;
}