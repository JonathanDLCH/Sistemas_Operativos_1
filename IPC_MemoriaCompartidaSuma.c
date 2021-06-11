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

	int n=atoi(argv[1]),i,j;
	key_t keypar,keyimp,keysuma;
	keypar=ftok("/home/jonathan/Escritorio/",'a');
	keyimp=ftok("/home/jonathan/Escritorio/",'b');
	keysuma=ftok("/home/jonathan/Escritorio/",'c');
	int idpar,idimp,idsuma;
	int *p_par,*p_imp,*p_sum;
	int vectorimpares[n],vectorpares[n],vectorsuma[n];

	idpar=shmget(keypar,sizeof(vectorpares),IPC_CREAT | 0777);
	idimp=shmget(keyimp,sizeof(vectorimpares),IPC_CREAT | 0777);
	idsuma=shmget(keysuma,sizeof(vectorsuma),IPC_CREAT | 0777);
	
	p_par=(int*)shmat(idpar,0,0);
	p_imp=(int*)shmat(idimp,0,0);
	p_sum=(int*)shmat(idsuma,0,0);


	for (i=0; i<n; i++){
		vectorpares[i]=p_par[i];
	}
	for (i=0; i<n; i++){
		vectorimpares[i]=p_imp[i];
	}
	
	for (int i=0; i<n; i++){
		p_sum[i]=vectorimpares[i]+vectorpares[i];
		vectorsuma[i]=p_sum[i];
		printf(" %d + %d = %d\n",vectorpares[i],vectorimpares[i],vectorsuma[i]);
	}

	shmdt(p_sum);
	shmdt(p_imp);
	shmdt(p_sum);
	shmctl(idpar,IPC_RMID,NULL);
	shmctl(idimp,IPC_RMID,NULL);
	shmctl(idsuma,IPC_RMID,NULL);

	return 0;
}