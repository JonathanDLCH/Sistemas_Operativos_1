#include <stdio.h>

#define tam 10

int i[tam];
float f[tam];
double d[tam];

int main(int argc, char const *argv[])
{
	printf("\t\t  Integer\t\t   Float\t\t   Double");
	printf("\n=============================================================================");

	for (int index = 0; index < tam; ++index)
	{
		printf("\nElement %d:\t %d\t\t %d\t\t %d",index,&i[index],&f[index],&d[index]);
	}

	printf("\n=============================================================================\n");
	return 0;
}