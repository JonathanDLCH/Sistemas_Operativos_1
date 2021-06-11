/*
Benemerita Universidad Autonoma de Puebla
Jonathan De La Cruz Huerta

Sincronizacion de procesos
Escribir 5 numeros continuos usando Pipes y Memoria compartida.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>

//#define rep 50

void GenerarPares(int t3,int t1,int idseg,int *pointer,int rep);
void GenerarImpares(int t1,int t2,int idseg,int *pointer,int rep);
void ConsumirNumeros(int t2,int t3,int idseg,int *pointer,int rep);
int par=0,impar=1;

int main(int argc, char *argv[]){
	if(argv[1]==NULL && atoi(argv)>=10){
		perror("Ingrese en consola el numero de datos.\nCondicion: n>=10");
		exit(-1);
	}
	int rep=atoi(argv[1]);
	key_t key=ftok(".",'a');
	int idseg,*pointer;
	
	//Tuberias utilizadas para sincronizar a los procesos p1,p2 y p3
	char testigo;
	int t1[2],t2[2],t3[2];

	int pid1,pid2;

	//Memoria utilizada como mecanismo de comunicacion entre los procesos
	idseg=shmget(key,sizeof(int)*20,IPC_CREAT|0777);

	//El proceso padre, que crea las tuberia, sera el proceso p1
	if(pipe(t1)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}
	if(pipe(t2)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}
	if(pipe(t3)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}

	switch(pid1=fork()){
		case -1:
				perror("Error al crear al proceso.");
				//Se cierra el pipe
				close(t1[0]); close(t1[1]);
				close(t2[0]); close(t2[1]);
				close(t3[0]); close(t3[1]);
				//Liberamos memoria
				shmdt(pointer);
				shmctl(idseg,IPC_RMID,NULL);
				exit(-1);
				break;
		case 0:
				//Este proceso lee de t1 y escribe en t2
				close(t3[0]); close(t3[1]);
				close(t1[1]);
				close(t2[0]);

				GenerarImpares(t1[0],t2[1],idseg,pointer,rep);

				//El proceso termina cerrando los descriptores
				close(t1[0]);
				close(t2[1]);
				//close(t3[1]);
				break;
		default:
				switch((pid2=fork())){
					case -1:
							perror("Error al crear el proceso.");
							//Se cierra el pipe
							close(t1[0]); close(t1[1]);
							close(t2[0]); close(t2[1]);
							close(t3[0]); close(t3[1]);
							//Liberamos memoria
							shmdt(pointer);
							shmctl(idseg,IPC_RMID,NULL);
							kill(pid1,SIGKILL);
							exit(0);
							break;
					case 0:
							//Cerramos el descriptor de escritura del pipe
							//close(t3[1]);
							close(t1[0]); close(t1[1]);
							close(t2[1]);
							close(t3[0]);
							
							ConsumirNumeros(t2[0],t3[1],idseg,pointer,rep);

							//Liberamos memoria
							shmdt(pointer);
							shmctl(idseg,IPC_RMID,NULL);
							close(t2[0]);
							close(t3[1]);
							exit(0);
							break;
					default:
							//Este proceso lee de t3 y escribe en t1
							close(t2[0]); close(t2[1]);
							close(t1[0]);
							close(t3[1]);

							GenerarPares(t3[0],t1[1],idseg,pointer,rep);

							//El proceso termina cerrando los descriptores
							close(t1[1]);
							close(t3[0]);
				}
	}
	
	return 0;
}

void GenerarPares(int t3,int t1,int idseg,int *pointer,int rep){
	char testigo;
	pointer=(int*)shmat(idseg,0,0);

	for (int n=0; n<5; n++){
		pointer[n]=par;
		par= par+2;
	}

	//Cede el turno a p2
	write(t1,&testigo,sizeof(char));

	for(int i=0;i<rep-5;i++){
		//Espera el turno
		read(t3,&testigo,sizeof(char));
		pointer=(int*)shmat(idseg,0,0);

		for (int n=0; n<5; n++){
			pointer[n]=par;
			par= par+2;
		}

		//Cede el turno a p2
		write(t1,&testigo,sizeof(char));
	}
}

void GenerarImpares(int t1,int t2,int idseg,int	 *pointer,int rep){
	int i=0;
	char testigo;

	for(i=0;i<rep;i++){
		//printf("rep impares i: %d\n",i );
		//Espera el turno
		read(t1,&testigo,sizeof(char));
		pointer=(int*)shmat(idseg,0,0);

		for(int n=5; n<10;n++){			
			pointer[n]=impar;
			impar= impar+2;
		}

		//Cede el turno a p1
		write(t2,&testigo,sizeof(char));

	}
}

void ConsumirNumeros(int t2,int t3,int idseg,int *pointer,int rep){
	char testigo;
	int cont=rep;

	while(cont>0){

		pointer=(int*)shmat(idseg,0,0);

		read(t2,&testigo,sizeof(char));
		for(int i=0;i<10 ;i++){
			printf("%d\n",pointer[i]);
		}
		cont=cont-10;
		write(t3,&testigo,sizeof(char));
	}
}