/*	FCC-BUAP
	Jonathan De La Cruz Huerta 201731754

	Sistemas Operativos 1

	Servidor
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#define buffer 50

struct DATA{
	pid_t pid;
	char name[buffer];
}clientedata,*p_data;

struct stat statbuf;

int main(int argc, char *argv[]){
	key_t key=ftok("/home/jonathan/Escritorio/",'j'); //Clave de datos recibidos
	key_t keydoc=ftok("/home/jonathan/Escritorio/",'m'); //Clave de archivo
	int idseg,iddoc,fd,bytes,i;
	char *p_doc;

//Obtenemos los datos de la peticion.
	idseg=shmget(key,sizeof(struct DATA), IPC_CREAT | 0777);
	p_data=(struct DATA*)shmat(idseg,0,0);

	clientedata.pid=p_data->pid;
	for(i=0;p_data->name[i]!='\0';i++){
		clientedata.name[i]=p_data->name[i];
	}
	printf("\nID: %d\nName file: %s\n",clientedata.pid,clientedata.name);

	shmdt(p_data); //Liberamos el puntero
	shmctl(idseg,IPC_RMID,NULL); //Liberamos el segmento

//Abrimos el archivo
	fd=open(clientedata.name,0);
	if(fd >= 0){ //Verificamos la existencia del archivo
		if(stat(clientedata.name,&statbuf) < 0){
			perror("Error_STAT: ");
			exit(-1);
		}
		iddoc=shmget(keydoc,statbuf.st_size, IPC_CREAT | 0777);
		p_doc=(char *)shmat(iddoc,0,0);

		for(i=0,bytes=1;bytes>0;i++){ //Escribimos en el segmento
			bytes=read(fd,&p_doc[i],sizeof(char));
		}

		kill(clientedata.pid,SIGUSR1); //Señal de disponibilidad
	}else{
		perror("\nDocument not found ");
		kill(clientedata.pid,SIGKILL);
		exit(-1);
	}
	
	return 0;
}