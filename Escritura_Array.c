/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754
Sistemas Operativos 1

Escritura de 1 arreglo
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp; //Puntero a archivo

	char* dir=argv[1]; //El parametro 1 indica el nombre del archivo.
	printf("\nName file: %s\n",dir);
	
	int tam= atoi(argv[2])+1;//El parametro 2 indica el numero de elementos.
	int array[tam]; //Se añade un dato mas por el parametro 2
	printf("\nElements number: %d\n",tam);

	for (int i = 0; i < tam; i++)
	{
		array[i]=*argv[i+2];
		printf("Writing... %c\n",array[i]);
	}

	if((fp = fopen(dir,"wb"))== NULL){ //Abrimos el archivo en modo write binary
		fprintf(stderr, "\nError opening file.");
	}

	if(fwrite(array,sizeof(array),1,fp) != 1){  //Escribimos todo el arreglo al archivo
		fprintf(stderr, "\nError to write file.");
	}else{
		printf("\nSuccessful operation.\n");
	}

	fclose(fp); //Cerramos el archivo
	return 0;
}