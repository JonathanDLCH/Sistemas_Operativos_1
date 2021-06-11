/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Armado de una señal
Numeros Pares e Impares
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <signal.h>

#define size 10

void suma(){
	int par,impar;
	int df_p=open("Par.dat",0),df_i=open("Impar.dat",0);

	for (int i=0; i<size;i++)
	{
		read(df_p,&par,sizeof(int));
		read(df_i,&impar,sizeof(int));
		printf("\n %d+%d=%d",par,impar,(par+impar));
	}
	close(df_p);
	close(df_i);
}

int main(int argc, char const *argv[])
{
	pid_t pid_P,pid_Q;
	int df_p=creat("Par.dat",0777),df_i=creat("Impar.dat",0777),i,j,k;
	pid_P=fork();
	if(pid_P>0){ //El padre ejecutara la señal
		printf("\nPadre_P:%d,ID_P: %d\n",getppid(),getpid());

		pid_Q=fork();
		if (pid_Q==0){ //Numeros pares
			printf("\nPadre_Q:%d,ID_Q: %d\n",getppid(),getpid());
			df_p=open("Par.dat",1);
			//printf("\nEscribiendo datos Pares");
			for (i=0,j=2; i<size;i++,j+=2){
				write(df_p,&j,sizeof(int));
				//printf("\n%d",j);
			}
			close(df_p);
			kill(getppid(),SIGUSR1);
			exit(1);
		}

		struct sigaction s;
		s.sa_handler=suma;
		sigemptyset(&s.sa_mask);
		s.sa_flags=0;

		if(sigaction(SIGUSR2,&s,NULL)&&sigaction(SIGUSR1,&s,NULL)){
			sigaction(SIGUSR1,&s,NULL);
		}else{
			pause();
		}
	}
	if(pid_P==0){ //EL hijo creara procesos para entrada de datos
		printf("\nPadre_Phijo:%d,ID_PHijo: %d\n",getppid(),getpid());
		df_i=open("Impar.dat",1);
		//printf("\nEscribiendo datos Impares");
		for (i=0,k=1; i<size;i++,k+=2){
			write(df_i,&k,sizeof(int));
			//printf("\n%d",k);
		}
		close(df_i);
		kill(getppid(),SIGUSR2);
		exit(1);
	}

	return 0;
}