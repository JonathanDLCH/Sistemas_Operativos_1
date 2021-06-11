/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Abanico de procesos:
testsim
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>

int main(int argc, char *argv[]){
	int t_suspension=atoi(argv[1]);
	int f_repeticion=atoi(argv[2]);
	pid_t pid;
	for (int i=0; i<f_repeticion; i++){
		pid=fork();
		if(pid>0){
			sleep(t_suspension);
		}
		if(pid==0){
			break;
		}
	}
	printf("\nEl padre del proceso %d es %d",getpid(),getppid());
	return 0;
}