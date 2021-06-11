/*

Benemerita Universidad Autonoma de Puebla
Jonathan De La Cruz Huerta

Sincronizacion de procesos
Usando Pipes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define rep 50

void GenerarPares(int tuberia,int t1, int t2);
void GenerarImpares(int tuberia,int t1, int t2);
void ConsumirNumeros(int tuberia);

int main(int argc, char *argv[]){

	//Tuberia utilizada como mecanismo de comunicacion entre los procesos
	int tuberia[2],t1[2],t2[2];

	//Tuberias utilizadas para sincronizar a los procesos p1 y p2
	int pid1,pid2;

	//El proceso padre, que crea la tuberia, sera el proceso p1
	if(pipe(tuberia)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}
	if(pipe(t1)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}
	if(pipe(t2)<0){
		perror("No se puede crear la tuberia");
		exit(-1);
	}

	switch(pid1=fork()){
		case -1:
				perror("Error al crear al proceso.");
				//Se cierra el pipe
				close(tuberia[0]);
				close(tuberia[1]);
				close(t1[0]); close(t1[1]);
				close(t2[0]); close(t2[1]);
				exit(-1);
				break;
		case 0:
				//Cerramos el descriptor de lectura del pipe
				close(tuberia[0]);

				//Este proceso lee de t1 y escribe en t2
				close(t1[1]);
				close(t2[0]);

				GenerarImpares(tuberia[1],t1[0],t2[1]);

				//El proceso termina cerrando los descriptores
				close(tuberia[1]);
				close(t1[0]);
				close(t2[1]);
				break;
		default:
				switch((pid2=fork())){
					case -1:
							perror("Error al crear el proceso.");
							//Se cierra el pipe
							close(tuberia[0]);
							close(tuberia[1]);
							close(t1[0]); close(t1[1]);
							close(t2[0]); close(t2[1]);
							kill(pid1,SIGKILL);
							exit(0);
							break;
					case 0:
							//Cerramos el descriptor de escritura del pipe
							close(tuberia[1]);
							close(t1[0]); close(t1[1]);
							close(t2[0]); close(t2[1]);

							ConsumirNumeros(tuberia[0]);

							close(tuberia[0]);
							exit(0);
							break;
					default:
							//Cerramos el descriptor de lectura del pipe
							close(tuberia[0]);

							//Este proceso lee de t2 y escribe en t1
							close(t1[0]);
							close(t2[1]);

							GenerarPares(tuberia[1],t1[1],t2[0]);

							//El proceso termina cerrando los descriptores
							close(tuberia[1]);
							close(t1[1]);
							close(t2[0]);
				}
	}
	
	return 0;
}

void GenerarPares(int tuberia,int t1, int t2){
	int i=0;
	char testigo;

	write(tuberia,&i,sizeof(int));

	//Cede el turno a p2
	write(t1,&testigo,sizeof(char));

	for(i=2;i<rep;i+=2){
		//Espera el turno
		read(t2,&testigo,sizeof(char));

		write(tuberia,&i,sizeof(int));

		//Cede el turno a p2
		write(t1,&testigo,sizeof(char));
	}
}

void GenerarImpares(int tuberia,int t1,int t2){
	int i=0;
	char testigo;

	for(i=1;i<rep;i+=2){
		//Espera el turno
		read(t1,&testigo,sizeof(char));

		write(tuberia,&i,sizeof(int));

		//Cede el turno a p1
		write(t2,&testigo,sizeof(char));
	}
}

void ConsumirNumeros(int tuberia){
	int i;

	while(read(tuberia,&i,sizeof(int))>0){
		sleep(1);
		printf("%d\n", i);
	}
}