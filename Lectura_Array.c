/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Lectura de 1 arreglo
*/
#include <stdio.h>
#define buffersize 100

int main(int argc, char *argv[])
{
	FILE *fp;
	char* dir=argv[1]; //El parametro 1 indica el nombre del archivo.
	int buffer[buffersize],i=1;

	if((fp = fopen(dir,"rb"))== NULL){ //Abrimos el archivo en modo read binary
		fprintf(stderr, "\nError opening file.");
	}

	fread(buffer,sizeof(buffer),buffersize,fp);

	printf("Array:\n");
	while(buffer[i] <= buffer[0] && buffer[i+1] != '\0'){ //Escribimos todo el arreglo al archivo
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");

	fclose(fp);
	return 0;
}