/*

Benemerita Universidad Autonoma de Puebla
Jonathan De La Cruz Huerta

Comunicacion multiples

A: Enviara las estructuras al segundo pograma por FIFO
B:Genera n estructuras data y los envia al proceso A por PIPES.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/stat.h>

struct data{
	float x;
	int y;
	char cad[20];
};

int main(int argc, char *argv[]){
	pid_t pid;
	int fd[2],status;
	int n=atoi(argv[1]),i,c;
	int fdfifo;
	struct data estructuras[n];

	pipe(fd);
	pid=fork();
	switch(pid){
		case -1: 
			perror("Error");
			exit(-1);
			break;
		case 0:
			close(fd[0]);
			printf("______Proceso B______\n");
			for(i=0;i<n;i++){
				while((c=getchar()) != '\n' && c!=EOF); //Vacia el buffer de manera correcta
				printf("Estructura %d\n",i+1 );
				printf("Cadena:\n");
				fgets(estructuras[i].cad,20,stdin);
				estructuras[i].cad[strlen(estructuras[i].cad)-1]='\0';
				printf("Float:\n");
				scanf("%f",&estructuras[i].x);
				printf("Int:\n");
				scanf("%d",&estructuras[i].y);

				write(fd[1],&estructuras[i],sizeof(estructuras));
			}
			break;
		default:
			wait(&status);
			close(fd[1]);
			printf("______Proceso A______\n");
			mkfifo("/home/jonathan/Escritorio/fifo",0777);
			fdfifo=open("/home/jonathan/Escritorio/fifo",O_WRONLY);
			for(i=0;i<n;i++){
				read(fd[0],&estructuras[i],sizeof(estructuras));
				printf("Estructura %d\n",i+1 );
				printf("Cadena: %s \n",estructuras[i].cad);
				printf("Float: %f \n",estructuras[i].x);
				printf("Int: %d \n",estructuras[i].y);
				write(fdfifo,&estructuras[i].cad,sizeof(estructuras->cad));
				write(fdfifo,&estructuras[i].x,sizeof(estructuras->x));
				write(fdfifo,&estructuras[i].y,sizeof(estructuras->y));
			}
	}
	
	return 0;
}