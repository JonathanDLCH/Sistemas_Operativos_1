/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

FIFO: Reader

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd;
	char dir[]="/home/jonathan/Escritorio/fifo",ms[30];

	fd=open(dir,O_RDONLY);
	read(fd,ms,sizeof(ms));
	printf("\nMensaje recibido: %s \n",ms);
	close(fd);
	return 0;
}