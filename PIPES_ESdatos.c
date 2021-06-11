/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

PIPES:
Lectura de n datos
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd[2],i,n,x;

	pipe(fd);
	pid=fork();
	n=atoi(argv[1]);

	if(pid>0){
		close(fd[1]);
		for (int i = 0; i < n; i++){
			read(fd[0],&x,sizeof(int));
			printf("\n%d",x);
		}
	}

	if(pid==0){
		close(fd[0]);
		for (int i = 0; i < n; i++){
			write(fd[1],&i,sizeof(int));
		}
	}
	return 0;
}