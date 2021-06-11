#include <stdio.h>

int main(int argc, char *argv[])
//El parametro arc es el numero de parametros que se le estan pasando al main
//El parametro argv[] son las cadenas de parametros que se le estan pasando al main
{
	char* objeto=argv[0];

	printf("\nParametro: %s Variable: %s\n", argv[0],objeto);
	return 0;
}