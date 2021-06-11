#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

int main(int argc, char const *argv[])
{
	int array1[SIZE],array2[SIZE];
	FILE *fp;

	for (int i = 0; i < SIZE; ++i)
	{
		array1[i]=i;
	}

	if ((fp = fopen("/home/jonathan/Escritorio/BUAP/Sistemas_Operativos/Archivo2.dat","wb"))==NULL)
	{
		fprintf(stderr, "\nError opening file.");
		exit(1);
	}

	if (fwrite(array1,sizeof(int),SIZE,fp)!=SIZE)
	{
		fprintf(stderr, "\nError writing to file.");
		exit(1);
	}

	fclose(fp);

//-------------Lectura-------------

	if ((fp = fopen("/home/jonathan/Escritorio/BUAP/Sistemas_Operativos/Archivo2.dat","rb"))==NULL)
	{
		fprintf(stderr, "\nError opening file.");
		exit(1);
	}

	if (fread(array2,sizeof(int),SIZE,fp)!=SIZE)
	{
		fprintf(stderr, "\nError writing to file.");
		exit(1);
	}

	fclose(fp);

	for (int i = 0; i < SIZE; ++i)
	{
		printf("%d\t%d\n", array1[i],array2[i]);
	}

	return 0;
}