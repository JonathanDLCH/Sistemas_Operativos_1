/*
	msgtool
	Utilidad de manejo de las colas de mensajes del sistema IPC SYSV
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf{
	long mtype;
	char mtext[MAX_SEND_SIZE];
};

void send_message(int qid,struct mymsgbuf *qbuf,long type,char *text);
void read_message(int qid,struct mymsgbuf *qbuf,long type);
void remove_queue(int qid);
void change_queue_mode(int qid,char *mode);
void usage(void);

int main(int argc, char *argv[]){
	key_t key;
	int msgqueue_id;
	struct mymsgbuf qbuf;

	if(argc == 1){
		usage();
	}

	//Crear clave unica mediante ftok()
	key=ftok(".",'m');

	//Abrir la cola --crearla si es necesario
	if((msgqueue_id = msgget(key,IPC_CREAT | 0660)) == -1){
		perror("msgget");
		exit(-1);
	}

	switch(tolower(argv[1][0])){
		case 'e':send_message(msgqueue_id,(struct mymsgbuf*)&qbuf,atol(argv[2]),argv[3]);
			break;
		case 'r':read_message(msgqueue_id,&qbuf,atol(argv[2]));
			break;
		case 'b': remove_queue(msgqueue_id);
			break;
		case 'm': change_queue_mode(msgqueue_id,argv[2]);
			break;
		default: usage();
	}
	return 0;
}

void send_message(int qid,struct mymsgbuf *qbuf,long type,char *text){
	//Enviar mensaje a la cola
	printf("Enviando mensaje...\n");
	qbuf->mtype=type;
	strcpy(qbuf->mtext,text);
	
	if((msgsnd(qid,(struct mymsgbuf *)qbuf,strlen(qbuf->mtext)+1,0)) == -1){
		perror("msgsnd");
		exit(-1);
	}
}

void read_message(int qid,struct mymsgbuf *qbuf,long type){
	//Leer mensaje de la cola
	printf("Leyendo mensaje...\n");
	qbuf->mtype=type;
	msgrcv(qid,(struct mymsgbuf *)qbuf,MAX_SEND_SIZE,type,0);

	printf("Tipo: %ld Texto: %s\n",qbuf->mtype,qbuf->mtext);
}

void remove_queue(int qid){
	//Borrado de la cola
	msgctl(qid,IPC_RMID,0);
}

void change_queue_mode(int qid,char *mode){
	struct msqid_ds myqueue_ds;
	//Obtener informacion actual
	msgctl(qid,IPC_STAT,&myqueue_ds);
	//Convertir y cargar el modo
	sscanf(mode,"%ho",&myqueue_ds.msg_perm.mode);
	//Actualizar el modo
	msgctl(qid,IPC_SET,&myqueue_ds);
}

void usage(void){
	fprintf(stderr, "msgtool -Utilidad de manejo de colas de mensajes\n");
	fprintf(stderr, "\nUSO: msgtool (e)nviar <tipo> <texto>\n");
}