/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Estructura compartida_A
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
	key_t key;
	int id,c;

	key=ftok("/home/jonathan/Escritorio/",'d');

	id=shmget(key,sizeof(struct DATA),IPC_CREAT | 0777);
	ptr=(struct DATA*)shmat(id,0,0);
	printf("\nIngrese n:");
	scanf("%d",&data.n);
	printf("\nIngrese car:");
	while((c=getchar()) != '\n' && c!=EOF); //Vacia el buffer de manera correcta
	scanf("%c",&data.car);
	ptr->n=data.n;
	ptr->car=data.car;
	return 0;
}