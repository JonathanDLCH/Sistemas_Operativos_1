#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CANON 100

/* Funcion para sacar renglones o lineas del archivo. */ 
void line(int df, char str[])
{
	int i = 0;
	char c;
	do{
    	read(df, &c, sizeof(c));
    	str[i] = c;
    	//printf("%c", c);
    	i++;
	}while(c != '-');
}
 
int main(int argc, char **argv)
{
	int i, j, k, bytes;
	int pr_limit, pr_count;
	int childpid;
	int df, status;
	char c;
	char *argumentos[6], str[MAX_CANON], word[MAX_CANON];
	char *ptrToken;
    df = open("programas.txt", 0);

    // Comprueba el número valido de argumentos en la linea de comandos
	if(argc != 2)
	{
		perror("Error en argc");
		exit(1);
	}

	pr_limit = atoi(argv[1]);	// Especifica el numero maximo de hijos que se permite ejecutar al mismo tiempo
	pr_count = 0;	// Contiene el numero de hijos activos. El valor inicial es 0 
	
	do{
		//line(df, str);
		// Algoritmo 1 para sacar renglones o lineas del archivo.
		i = 0;
		do{
	    	bytes = read(df, &c, sizeof(c));
	    	str[i] = c;
	    	i++;
		}while(c != '\n');
		// Fin del Algoritmo 1 
		// Algoritmo 2 para separar la cadena por el token espacio 
		k = 0;
		ptrToken = strtok(str, " ");
		while(ptrToken != NULL)
		{
			argumentos[k++] = ptrToken;
			ptrToken = strtok(NULL, " ");
		}
		for(i = 0; i < k; i++)
			printf("%s\n", argumentos[i]);
		// Fin de ALgoritmo 2
		/*if(pr_count == pr_limit)
		{
			/// EL proceso debe esperar a que el hijo termine y disminuir el valor pr_count 
			waitpid(-1, &status, 0);	//7 -1 para esperar la finalizacion de cualquier proceso
			pr_count--;
		}*/

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

		/*if(waitpid(-1, NULL, WNOHANG) != 0) // Comprueba si algun hijo ha terminado
			pr_count--;*/

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

   	/*pid_t childpid=0;
    int pr_limit, pr_count=0, status;
    char s[MAX_BUF], program[MAX_BUF], num1[MAX_BUF], num2[MAX_BUF];

    if(argc!=2){ /* comprueba el número válido de argumentos de línea de comandos *
        fprintf(stderr, "Uso: %s (int) <nombre de archivo\n", argv[0]);
        return 1;
    }

    pr_limit=atoi(argv[1]);

	while(fgets(s, 100, stdin))
	{
        /* comprueba pr_limit y espera a que un hijo termine si se alcanza *
        if(pr_count==pr_limit)
        {
            waitpid(-1, &status, 0);
            pr_count--;
            printf("Código de salida del hijo: %d\n", WEXITSTATUS(status));
        }

        /* lee en cadenas para comandos *
        sscanf(s, "%s %s %s", program, num1, num2);
        
        if((childpid=fork())<=0)
        {
        /* esto si el bucle detecta fallas el fork *
            if(childpid<0)
            {
                perror("Hijo no se pudo crear");
                return 1;
            }
            break;
        }

        pr_count++;

		* ejecuta comandos desde archivo en hijo *
       	if (childpid == 0)
       	{
             printf ("% s% s% s \n", programa, num1, num2);
             execl (programa, programa, num1, num2, NULL);
        } *

        / comprueba si algún niño ha terminado *

        if(waitpid(-1, NULL, WNOHANG)!=0){
            pr_count--;
        }
    }

    * ejecuta comandos desde archivo en hijo *

    if(childpid==0)
    {
        execl(program, program, num1, num2, NULL);
    }
 	while(1)
 	{
        childpid=waitpid(-1, &status, 0);
        if(childpid==-1){
            break;
        }
        pr_count--;
        printf("Código de salida del hijo: %d\n", WEXITSTATUS(status));
    }*/