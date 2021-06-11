/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

IPC
Memoria compartida:
Suma
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	int n=atoi(argv[1]),i,j,k;
	key_t key=ftok("/home/jonathan/Escritorio/",'a');
	int idseg,*ptr,*ptraux,*ptrpar,*ptrimp;
	int vector[n*3];

	idseg=shmget(key,sizeof(vector),IPC_CREAT | 0777);
	
	ptr=(int*)shmat(idseg,0,0);
	ptrpar=ptr;
	ptrimp=ptr;
	ptraux=ptr;

	for (i=0,j=n,k=2*n; i<n; i++,j++,k++){
		vector[k]=ptrpar[i]+ptrimp[j];
		printf("\nvector k= %d",vector[k]);
		ptraux[k]=vector[k];
	}

	for (i=0,j=n,k=2*n; i<n; i++,j++,k++){
		printf(" %d + %d = %d\n",ptrpar[i],ptrimp[j],ptraux[k]);
	}

	shmdt(ptr);
	shmdt(ptrpar);
	shmdt(ptrimp);
	shmctl(idseg,IPC_RMID,NULL);

	return 0;
}