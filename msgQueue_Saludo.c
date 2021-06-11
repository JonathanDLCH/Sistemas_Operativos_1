/*	FCC-BUAP
	Jonathan De La Cruz Huerta 201731754

	Sistemas Operativos 1

	Message Queue -IPC
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
	long type;
	char text[20];
	int edad;
};

int main(int argc, char *argv[]){

	int idQ;
	key_t key=ftok(".",'a');
	pid_t pid;
	struct msgbuf msg1;
	struct msgbuf msg2;
	
	if((idQ=msgget(key,IPC_CREAT|0777))==-1){
		perror("Get");
		exit(-1);
	}

	pid=fork();
	switch(pid){
		case -1: perror("Fork");
			break;
		case 0:
				msg1.type=1;
				strcpy(msg1.text,"Hola papa");
				msg1.edad=atoi(argv[1]);
			//Enviamos informacion a la cola de mensajes
				if(msgsnd(idQ,&msg1,sizeof(msg1),0)==-1){
					perror("Send");
					exit(-1);
				}
			//Obtenemos informacion de la cola de mensajes
				if(msgrcv(idQ,&msg2,sizeof(msg2),2,0)==-1){
					perror("Receive");
					exit(-1);
				}
				printf("ID: %d ,Receive: %s ,mi edad es: %d\n",getpid(),msg2.text,msg2.edad);
			break;
		default:
				msg2.type=2;
				strcpy(msg2.text,"Hola hijo");
				msg2.edad=atoi(argv[2]);
			//Enviamos informacion a la cola de mensajes
				if(msgsnd(idQ,&msg2,sizeof(msg2),0)==-1){
					perror("Send");
					exit(-1);
				}
			//Obtenemos informacion de la cola de mensajes
				if(msgrcv(idQ,&msg1,sizeof(msg1),1,0)==-1){
					perror("Receive");
					exit(-1);
				}
				printf("ID: %d ,Receive: %s ,mi edad es: %d\n",getpid(),msg1.text,msg1.edad);
	}

	msgctl(idQ,IPC_RMID,0);
	return 0;
}