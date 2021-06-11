/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Señal Alarm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <signal.h>

#define n 10

void manejador();
pid_t pid;

int main(int argc, char *argv[]){
	int status,df,idhijo;
	df=creat("Id.dat",0777);
	df=open("Id.dat",2);

	pid=fork();
	if (pid>0)
	{
		struct sigaction s;
		s.sa_handler=manejador;
		sigemptyset(&s.sa_mask);
		//sigaddset(&s.sa_mask,SIGKILL);
		s.sa_flags=0;
		sigaction(SIGALRM,&s,NULL);
		alarm(5);
		printf("\nID-Padre: %d",getpid());
		wait(&status);

	}
	if(pid==0){
		for (int i=0; i<n; i++)
		{
			printf("%dID-Hijo: %d\n",i,getpid());
			idhijo=getpid();
			write(df,&idhijo,sizeof(int));
		}
		kill(getppid(),SIGALRM);
	}
	return 0;
}

void manejador(){
	printf("\n %d",getpid());
	kill(getpid(),SIGKILL);	
}