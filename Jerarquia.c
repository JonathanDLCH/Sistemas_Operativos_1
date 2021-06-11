/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Proceso Wait: Pares e Impares
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_R,pid_L,pid_Q,pid_A,pid_Z,pid_N,pid_S,pid_K,pid_G,pid_D,pid_B;

	pid_R=fork(); //R
	if(pid_R>0){
		printf("\nID_R: %d\n",getpid());

		pid_L=fork();
		if(pid_L==0){
			printf("\nPadre_L:%d,ID_L: %d\n",getppid(),getpid());

			pid_K=fork();
			if (pid_K==0)
			{
				printf("\nPadre_K:%d,ID_K: %d\n",getppid(),getpid());
				exit(1);
			}

			pid_D=fork();
			if(pid_D==0){
				printf("\nPadre_D:%d,ID_D: %d\n",getppid(),getpid());
				exit(1);
			}

			pid_G=fork();
			if (pid_G==0)
			{
				printf("\nPadre_G:%d,ID_G: %d\n",getppid(),getpid());
				pid_B=fork();
				if(pid_B==0){
					printf("\nPadre_B:%d,ID_B: %d\n",getppid(),getpid());
					exit(1);
				}
			}
		}
	}

	if(pid_R==0){ //M
		printf("\nPadre_M:%d,ID_M: %d\n",getppid(),getpid());

		pid_Q=fork();
		if (pid_Q==0)
		{
			printf("\nPadre_Q:%d,ID_Q: %d\n",getppid(),getpid());
			exit(1);
		}
		pid_A=fork();
		if (pid_A==0)
		{
			printf("\nPadre_A:%d,ID_A: %d\n",getppid(),getpid());

			pid_Z=fork();
			if(pid_Z==0){
				printf("\nPadre_Z:%d,ID_Z: %d\n",getppid(),getpid());
				exit(1);
			}
			pid_N=fork(); //N
			if (pid_N==0)
			{
				printf("\nPadre_N:%d,ID_N: %d\n",getppid(),getpid());
				pid_S=fork(); //S
				if (pid_S==0)
				{
					printf("\nPadre_S:%d,ID_S: %d\n",getppid(),getpid());
					exit(1);
				}
			}
		}

	}
	return 0;
}