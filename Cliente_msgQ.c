/*	FCC-BUAP
	Jonathan De La Cruz Huerta 201731754

	Sistemas Operativos 1
	-IPC
	Message Queue-Cliente
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSGMAX 4056 //Tamaño maximo del mensaje (bytes)

struct msgbuf{
	long type;
	char namefile[40];
};

int main(int argc, char *argv[]){
	int idQ,n,i,menu;
	key_t key=ftok(".",'a');
	struct msgbuf data;

	if((idQ=msgget(key,IPC_CREAT|0777))==-1){
		perror("Get");
		exit(-1);
	}

	printf("Ingrese el NUMERO de archivos a abrir: \n");
	scanf("%d",&n);
/*
	for(i=0;i<n;i++){
		data.type=1;
		printf("Nombre archivo: \n");
		fgets(data.namefile,40,stdin);
		data.namefile[strlen(data.namefile)-1]='\0';
	}
*/
	do{
		printf("Nombre del archivo: \n");
		fgets(data.namefile,50,stdin);
		//Enviamos la informacion de la peticion
		if(msgsnd(idQ,&data,sizeof(data),IPC_WAIT)==-1){
			perror("Send");
			exit(-1);
		}
		printf("Desea hacer una nueva peticion: \n1)Si\n0)No");

	}while(menu!=0);

	msgctl(idQ,IPC_RMID,0);
	return 0;
}