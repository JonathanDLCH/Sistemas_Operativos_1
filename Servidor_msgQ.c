/*	FCC-BUAP
	Jonathan De La Cruz Huerta 201731754

	Sistemas Operativos 1
	-IPC
	Message Queue-Servidor
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf{
	long type;
	char namefile[30];
};

int main(int argc, char *argv[]){
	int idQ,i,menu;
	key_t key=ftok(".",'a');
	struct msgbuf data;

	if((idQ=msgget(key,IPC_CREAT|0777))==-1){
		perror("Get");
		exit(-1);
	}

	//Obtenemos informacion de la cola de mensajes
	if(msgrcv(idQ,&data,sizeof(data),1,0)==-1){
		perror("Receive");
		exit(-1);
	}
	printf("Receive: %s\n",data.text);

	
	return 0;
}