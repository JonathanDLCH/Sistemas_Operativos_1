/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Escritura de n reales
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp; //Puntero a archivo

	char* dir=argv[1],*dir2=argv[2]; //Nombres de los archivos. Parametro 1-2	
	int tam= atoi(argv[3])+1;//El parametro 2 indica el numero de elementos. Se añade un dato mas por el parametro 2
	int array[tam], *p_array,i;

	printf("\nName Binary file: %s",dir);
	printf("\nElements number: %d\n",tam);

	for (p_array=array,i=0; i<tam; p_array++,i++)
	{
		*p_array=*argv[i+2];
		printf("Writing...%c\n",*p_array);
	}

	if((fp = fopen(dir,"wb"))== NULL){ //Abrimos el archivo en modo write binary
		fprintf(stderr, "\nError opening file.");
	}

	for (p_array=array; *p_array != '\0'; p_array++)
	{
		fwrite(p_array,sizeof(p_array),1,fp); //Escribimos 1-1 al archivo
	}

	fclose(fp); //Cerramos el archivo

	printf("\nName Text file: %s",dir2);

	if((fp = fopen(dir2,"r"))== NULL){ //Abrimos el archivo en modo write binary
		fprintf(stderr, "\nError opening file.");
	}	

	return 0;
}