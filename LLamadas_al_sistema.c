/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Llamadas al sistema
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int df,tam,i;
	char *dir = argv[1]; //Nombre del archivo
	tam=atoi(argv[2])+1; //tamaño del arreglo
	int num[tam],*p_num;

	df=creat(dir,0777); //Creamos el archivo con permisos.
	
	if(open(dir,2) == df){ //Abrimos el archivo y verificamos si existe algun error
		fprintf(stderr, "\nError opening file.");
	}

	for (p_num=num,i=0; i<tam; p_num++,i++)
	{
		*p_num=*argv[i+2];
		printf("Writing...%c\n",*p_num);
	}

	for (p_num=num, i = 0; i < tam; p_num++,i++)
	{
		write(df,p_num,sizeof(int)); //Escribimos en el archivo.
	}

	close(df);

	printf("\n-------------------------------------------\n");

	open(dir,2);

	for (p_num=num, i = 0; i < tam; p_num++,i++)
	{
		read(df,p_num,sizeof(int)); //Leemos el archivo.
		printf("Reading...%c\n",*p_num );
	}

	close(df);

	return 0;
}
/*
Asesorias:

	Lunes y Miercoles: 12:00-1:00
	Cubiculo 114(COO2)

*/