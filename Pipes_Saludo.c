/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Pipes Saludo hijo-padre
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>

#define SIZE 100

int main(int argc, char  *argv[]){
	pid_t pid;
	int pipeA[2],pipeB[2],readbytes,status;
	char buffer[SIZE];

	pipe(pipeA);
	pipe(pipeB);

	if ( (pid=fork()) == 0 ){ // hijo
	    close( pipeA[1] ); /* cerramos el lado de escritura del pipe */
	    close( pipeB[0] ); /* cerramos el lado de lectura del pipe */
	 
	    while( (readbytes=read( pipeA[0], buffer, SIZE ) ) > 0){
	      write( 1, buffer, readbytes );
	    }
	    close( pipeA[0] );
	 
	    strcpy( buffer, "Mensaje enviado por hijo: Hola padre.\n" );
	    write( pipeB[1], buffer, strlen( buffer ) );
	    close( pipeB[1] );
	}else{ // padre
	    close( pipeA[0] ); /* cerramos el lado de lectura del pipe */
	    close( pipeB[1] ); /* cerramos el lado de escritura del pipe */
	 
	    strcpy( buffer, "Mensaje enviado por padre: Hola hijo.\n" );
	    write( pipeA[1], buffer, strlen( buffer ) );
	    close( pipeA[1]);
	 
	    while( (readbytes=read( pipeB[0], buffer, SIZE )) > 0){
	      write( 1, buffer, readbytes );
	    }
	    close( pipeB[0]);
	}
  	waitpid( pid, NULL, 0 );
	
	return 0;
}