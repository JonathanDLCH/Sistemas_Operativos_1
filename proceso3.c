/*   W     W : Lee la informacion de los archivos y suma elemento a elemento e imprime a pantalla
    / \    Q : Escribe 10 enteros pares en datos1.dat
   Q   L   L : Escribe 10 enteros impares en datos2.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define MAX 10
void main ()
{
	pid_t pidQ, pidL;
	int n, fd1, fd2, count, x, y;
	time_t t;

	srand((unsigned) time(&t));	//para que no se repitan los numero aleatorios en cada compilacion
	pidQ = fork();

	if(pidQ == 0)	// Q
	{
		fd1 = creat("datos1.dat", 0777);
		fd1 = open("datos1.dat", 1);
		for(count = 0; count < MAX; count++)
		{
			do{
				n = rand() % 100;
			}while( n % 2 != 0);
			write(fd1, &n, sizeof(int));
		}
	}
	
	if(pidQ > 0) // W
	{
		pidL = fork();
		if(pidL == 0)	// L
		{
			fd2 = creat("datos2.dat", 0777);
			fd2 = open("datos2.dat", 1);
			for(count = 0; count < MAX; count++)
			{
				do{
					n = rand() % 100;
				}while( n % 2 == 0);
				write(fd2, &n, sizeof(int));
			}
		}
		sleep(6);
		if (pidL > 0)	// L
		{
			fd1 = open("datos1.dat", 0);
			fd2 = open("datos2.dat", 0);
			for(count = 0; count < MAX; count++)
			{
				read(fd1, &x, sizeof(int));
				read(fd2, &y, sizeof(int));
				printf("%d + %d = %d\n", x, y, (x+y));
			}
		}
	}
}
