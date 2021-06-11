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

pid_t pid;
int n=1;
void manejador1(){
	int df,n;
	df=open("numeros.dat",0);
	read(df,&n,sizeof(int));
	printf("\nReading: %d",n);
	close(df);
}

void manejador2(){
	int df;
	df=open("numeros.dat",1);
	write(df,&n,sizeof(int));
	n++;
}

int main(int argc, char *argv[])
{
	int n,df,status;
	df=creat("numeros.dat",0777);	

	pid=fork();
	if(pid>0){
		struct sigaction s;
		s.sa_handler=manejador1;
		sigemptyset(&s.sa_mask);
		//sigaddset(&s.sa_mask,SIGKILL);
		s.sa_flags=0;
		sigaction(SIGALRM,&s,NULL);
		while(1){
			alarm(1);
			pause();
		}

	}
	if(pid==0){
		struct sigaction s2;
		s2.sa_handler=manejador2;
		sigemptyset(&s2.sa_mask);
		//sigaddset(&s.sa_mask,SIGKILL);
		s2.sa_flags=0;
		sigaction(SIGALRM,&s2,NULL);
		while(1){
			alarm(1);
			pause();
		}
	}
	return 0;
}