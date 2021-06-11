/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Escritura de n estructuras de Estudiantes (Con LLamadas al sistema).
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

//Prototipos
void clean();

typedef struct
{
	char name[50],matricula[30],gender,degree[50];
	int age;
}STUDENT;

int main(int argc, char *argv[])
{
	int df,tam,i;
	char *dir = argv[1]; //Nombre del archivo Text File.
	tam=atoi(argv[2]); //Tamaño del arreglo de estudiantes.

	df=creat(dir,0777);

	printf("\nFile name: %s",dir);
	printf("\nNu. students: %d",tam);

	STUDENT students[tam],*p_students;

	if(open(dir,2) == df){ //Abrimos el archivo
		fprintf(stderr, "\nError opening file.");
		exit(1);
	}

	for (p_students=students, i = 0; i < tam; p_students++,i++)
	{
		printf("\n %d-Student information",i+1);
		clean();
		printf("\nName: ");
		scanf("%s",p_students->name);
		clean();
		printf("\nAge: ");
		scanf("%d",&p_students->age);
		clean();
		printf("\nGender F/M: ");
		scanf("%c",&students->gender);
		printf("\nMatricula: ");
		scanf("%s",p_students->matricula);
		printf("\nDegree: ");
		scanf("%s",p_students->degree);

		write(df,p_students,sizeof(students)); //Escribimos en elarchivo
	}
	close(df);

	if(open(dir,2) == df){ //Abrimos el archivo
		fprintf(stderr, "\nError opening file.");
		exit(1);
	}
	
	return 0;
}

void clean(){
	int c;
	while((c=getchar()) != '\n' && c!=EOF); //Limpiamos buffer
}