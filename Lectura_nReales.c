/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Lectura de n reales
*/
#include <stdio.h>
#define buffersize 20

int main(int argc, char *argv[])
{
	FILE *fp,*fp2;
	char* dir=argv[1]; //El parametro 1 nombre del Binary File.
	char* dir2=argv[2]; //El parametro 2 nombre del Text File.
	int buffer[buffersize],i=1, *p_buffer;

	if((fp = fopen(dir,"rb"))== NULL){ //Abrimos el archivo en modo read binary
		fprintf(stderr, "\nError opening file.");
	}

	fread(buffer,sizeof(buffer),buffersize,fp);

	printf("Array:\n");
	while(buffer[i] <= buffer[0] && buffer[i+1] != '\0'){
		printf("%c\n", buffer[i]);
		i++;
	}
	fclose(fp);
	//-----------Manda a archivo de texto-----------
	if((fp2 = fopen(dir2,"w"))== NULL){ //Abrimos el archivo en modo read binary
		fprintf(stderr, "\nError opening file.");
	}
	p_buffer=buffer;

	while(*p_buffer != '\0'){ //Escribimos todo el arreglo al archivo
		fprintf(fp2,"%c", *p_buffer);
		p_buffer++;
	}

	fclose(fp2);
	return 0;
}