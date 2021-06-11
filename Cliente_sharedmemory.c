/*	FCC-BUAP
	Jonathan De La Cruz Huerta 201731754

	Sistemas Operativos 1

	Cliente
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#define buffer 50

void dri1();

struct DATA{
	pid_t pid;
	char name[buffer];
}clientedata,*p_data;

struct stat statbuf;

int main(int argc, char *argv[]){
	key_t key=ftok("/home/jonathan/Escritorio/",'j'); //clave para envio de datos
	int idseg,i;

	//Manejador
	struct sigaction s;
	s.sa_handler=dri1;
	s.sa_flags=0;
	sigemptyset(&s.sa_mask);
	sigaddset(&s.sa_mask,SIGKILL);
	sigaction(SIGUSR1,&s,NULL);

	idseg=shmget(key,sizeof(struct DATA),IPC_CREAT | 0777); //Obtenemos el segmento compartido
	p_data=(struct DATA*)shmat(idseg,0,0); //Apuntamos al segmento

	printf("\nEnter the file name: ");
	fgets(clientedata.name,buffer,stdin);
	clientedata.name[strlen(clientedata.name)-1]='\0'; //*Debemos quitar el salto de linea
	clientedata.pid=getpid();

	//Escribimos la estructura en la memoria compartida
	p_data->pid=clientedata.pid;
	for(i=0;clientedata.name[i]!='\0';i++){
		p_data->name[i]=clientedata.name[i];
	}

	pause(); //Esperamos la respuesta del servidor

	return 0;
}

void dri1(){ //Imprime el archivo
	key_t keydoc=ftok("/home/jonathan/Escritorio/",'m'); //Clave para leer archivo/shm
	int iddoc,i;
	char *p_doc;

	if(stat(clientedata.name,&statbuf) < 0){ //Obtenemos la informacion del archivo
		perror("Error_STAT: ");
		exit(-1);
	}

	iddoc=shmget(keydoc,statbuf.st_size*sizeof(char), IPC_CREAT | 0777);
	p_doc=(char *)shmat(iddoc,0,0);

	printf("\nThe file is available\n");

	for(i=0;p_doc[i]!='\0';i++){ //Imprimimos la memoria compartida
		printf("%c",p_doc[i]);
	}

	shmdt(p_doc); //Liberamos el puntero
	shmctl(iddoc,IPC_RMID,NULL); //Liberamos el segmento
}
/*
Alternativa para quitar el salto de linea de una cadena:
    while(getchar() != '\n');
*/