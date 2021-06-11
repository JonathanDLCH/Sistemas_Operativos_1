/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Armado de una señal
Escritura de 10 numeros
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <signal.h>

void leerdatos(){
	int n;
	int df=open("datos.dat",0);
	for (int i = 0; i < 10; i++){
		read(df,&n,sizeof(int));
		printf("\n %d",n);
	}
}

int main(){
	pid_t pid;
	int df=creat("datos.dat",0777);
	pid=fork();

	if(pid>0){
		struct sigaction s;
		s.sa_handler=leerdatos;
		sigemptyset(&s.sa_mask);
		s.sa_flags=0;

		sigaction(SIGUSR1,&s,NULL);
		pause();
	}

	if(pid==0){
		df=open("datos.dat",1);
		for (int i = 0; i < 10; i++){
			write(df,&i,sizeof(int));
		}
		kill(getppid(),SIGUSR1);
	}
	return 0;
}