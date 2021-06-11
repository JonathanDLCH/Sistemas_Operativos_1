/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Estructura compartida_B
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

struct DATA
{
	int n;
	char car;
}data,*ptr;

int main(int argc, char  *argv[]){
	int idseg;
	key_t key;

	key=ftok("/home/jonathan/Escritorio/",'d');
	idseg=shmget(key,sizeof(struct DATA),IPC_CREAT | 0777);
	ptr=(struct DATA*)shmat(idseg,0,0);
	for (int i=0; i < ptr->n ; i++){
		printf("\ncar:%c",ptr->car);
	}
	
	shmdt(ptr);
	shmctl(idseg,IPC_RMID,NULL);
	return 0;
}