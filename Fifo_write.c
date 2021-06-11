/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

FIFO: Writer

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	char dir[]="/home/jonathan/Escritorio/fifo",ms[]="Mensaje enviado por fifo";
	mkfifo(dir,0777);
	fd=open(dir,O_WRONLY);

	write(fd,ms,sizeof(ms));
	close(fd);
	return 0;
}

