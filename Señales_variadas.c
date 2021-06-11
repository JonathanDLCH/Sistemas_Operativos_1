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

int id[3];

void dri1();
void dri2();
void dri3();
void dri4();

int main(int argc, char *argv[])
{
	int df;
	df=creat("ID_BC.dat",0777);
	df=open("ID_BC.dat",2);
	pid_t pidR,pidA,pidB,pidC;

	pidR=fork();
	if(pidR>0){ //R
		id[0]=getpid();
		printf("\nR:%d",getpid());
		struct sigaction s;
		s.sa_handler=dri1;
		sigemptyset(&s.sa_mask);
		//sigaddset(&s.sa_mask,SIGKILL);
		s.sa_flags=0;
		sigaction(SIGUSR1,&s,NULL);
	}
	if (pidR==0){
		pidA=fork();
		if (pidA>0){ //A
			id[1]=getpid();
			while(1){
				printf("\nA:%d",getpid());
			}
			
			struct sigaction s2;
			s2.sa_handler=dri2;
			sigemptyset(&s2.sa_mask);
			//sigaddset(&s.sa_mask,SIGKILL);
			s2.sa_flags=0;
			sigaction(SIGUSR2,&s2,NULL);
		}
		if (pidA==0){
			pidB=fork();
			if (pidB>0){ //B
				id[2]=getpid();
				write(df,&id[2],sizeof(int));
				while(1){
					printf("\nB:%d",getpid());
				}
				struct sigaction s3;
				s3.sa_handler=dri3;
				sigemptyset(&s3.sa_mask);
				//sigaddset(&s.sa_mask,SIGKILL);
				s3.sa_flags=0;
				sigaction(SIGUSR1,&s3,NULL);

			}
			if (pidB==0){ //C
				id[3]=getpid();
				write(df,&id[3],sizeof(int));

				struct sigaction s4;
				s4.sa_handler=dri4;
				sigemptyset(&s4.sa_mask);
				//sigaddset(&s.sa_mask,SIGKILL);
				s4.sa_flags=0;
				sigaction(SIGALRM,&s4,NULL);
				alarm(6);
				while(1){
					printf("\nC:%d",getpid());
				}
				pause();
			}
		}
	}
	return 0;
}
void dri1(){
	for(int i=0;i<3;i++){
		kill(id[i],SIGKILL);
	}
	printf("\nSe terminaron los procesos");
}

void dri2(){
	kill(id[0],SIGUSR1);
}

void dri3(){
	kill(id[1],SIGUSR2);
}

void dri4(){
	kill(id[2],SIGUSR1);
}