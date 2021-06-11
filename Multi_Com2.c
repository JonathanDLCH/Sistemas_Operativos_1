/*

Benemerita Universidad Autonoma de Puebla
Jonathan De La Cruz Huerta

Comunicacion multiples

C: Enviara las estructuras al proceso D por MEMORIA COMPARTIDA.
D: Enviara las estructuras al proceso E por COLA de MENSAJES.
E: Imprime las estructura
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct data{
	float x;
	int y;
	char cad[20];
};

int main(int argc, char *argv[]){
	pid_t pidC,pidD;
	int fdfifo,n,i;
	n=atoi(argv[1]);
	struct data estructuras[n];

	pidC=fork();
	if(pidC>0){
		printf("pid C: %d, mi padre es: %d\n",getpid(),getppid());
		fdfifo=open("/home/jonathan/Escritorio/fifo",O_RDONLY);
		for(i=0;i<n;i++){
			read(fdfifo,&estructuras[i].cad,sizeof(estructuras->cad));
			read(fdfifo,&estructuras[i].x,sizeof(estructuras->x));
			read(fdfifo,&estructuras[i].y,sizeof(estructuras->y));
			printf("Estructura %d\n",i+1 );
			printf("Cadena: %s \n",estructuras[i].cad);
			printf("Float: %f \n",estructuras[i].x);
			printf("Int: %d \n",estructuras[i].y);
		}
	}
	if(pidC==0){

		pidD=fork();
		if(pidD>0){
			printf("pid D: %d, mi padre es: %d\n",getpid(),getppid());
		}
		if(pidD==0){
			printf("pid E: %d, mi padre es: %d\n",getpid(),getppid());
		}
	}
	return 0;
}