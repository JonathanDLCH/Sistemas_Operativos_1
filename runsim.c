/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Abanico de procesos:
runsim
Ejecucion de varios programas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CANON 50

void linea(int df, char str[]);
 
int main(int argc, char **argv)
{
	int i, j, k, bytes;
	int pr_limit, pr_count;
	int childpid;
	int df, status;
	char c;
	char *argumentos[6], str[MAX_CANON];
	char *ptrToken;
    
    df = open("Programas.txt", 0);
    if(df < 0)
    {
    	perror("Error en abrir el archivo");
    	exit(1);
    }
    // Comprueba el número valido de argumentos en la lineaa de comandos
	if(argc != 2)
	{
		perror("Error en argc");
		exit(1);
	}

	pr_limit = atoi(argv[1]);	// Especifica el numero maximo de hijos que se permite ejecutar al mismo tiempo
	pr_count = 0;	// Contiene el numero de hijos activos. El valor inicial es 0 
	
	do{
		//linea(df, str);
		// Algoritmo 1 para sacar renglones o lineaas del archivo.
		i = 0;
		do{
	    	bytes = read(df, &c, sizeof(char));
	    	if(bytes == -1)
	    	{
	    		perror("file");
	    		exit(1);
	    	}
	    	str[i] = c;
	    	i++;
		}while(c != '\n');
		
		//Separar la cadena por el token espacio 
		k = 0;
		ptrToken = strtok(str, " ");
		while(ptrToken != NULL)
		{
			argumentos[k++] = ptrToken;
			ptrToken = strtok(NULL, " ");
		}
		
		// Fin de ALgoritmo 2
		if(pr_count == pr_limit)
		{
			/// EL proceso debe esperar a que el hijo termine y disminuir el valor pr_count 
			waitpid(-1, &status, 0);	//7 -1 para esperar la finalizacion de cualquier proceso
			pr_count--;
		}

		childpid = fork();
		switch(childpid)
		{
			case -1: // error del fork()
					exit(-1);
			case 0: // proceso hijo
					execvp(argumentos[0], argumentos);
					perror("exec");
					break;
			default: // padre
					printf("Proceso padre\n");
		}
		
		pr_count++;	// Rastreo del numero de hijos activos

		if(waitpid(-1, NULL, WNOHANG) != 0) // Comprueba si algun hijo ha terminado
			pr_count--;

	}while(bytes != 0);	// Se termina el ciclo cuando bytes tenga un 0 que signfica que el archivo llego a su fin
	

	while(1)
	{
		childpid = waitpid(-1, &status, 0);
		if(childpid == -1)
			break;
		pr_count--;
	}
	return 0;
}

/* Funcion para sacar renglones o lineaas del archivo. */
void linea(int df, char str[]){
	int i = 0;
	char c;
	do{
    	read(df, &c, sizeof(c));
    	str[i] = c;
    	i++;
	}while(c != '-');
}