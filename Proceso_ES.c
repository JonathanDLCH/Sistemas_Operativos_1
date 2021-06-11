/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Proceso Lectura y Escritura de 10 numeros
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){

	int numbers[10], *p_number, df, i;
	char dir[]={"datos.dat"};
	pid_t pid;

	df=creat(dir,0777); //Creamos el archivo
	pid=fork(); //Creamos un proceso hijo

	if(pid>0){ //Proceso padre
		sleep(10); // Se duerme el proceso para ingresar los numeros.

		df=open(dir,0); //Importante asignar a df el archivo al abrir.
		if (read(df,numbers,sizeof(numbers))!=sizeof(numbers)){
			printf("\nError to read file.");
			exit(1);
		}
		for(i=0;i<10;i++){
			printf("\n%d-number: %d",i+1,numbers[i]);
		}
		close(df);
	}

	if(pid==0){ //Proceso hijo
		
		df=open(dir,1); //Importante asignar a df el archivo al abrir.
		for (p_number=numbers, i=0; i<10 ;p_number++, i++){
			printf("\nInsert %d-number",i+1);
			scanf("%d",p_number);

			if (write(df,p_number,sizeof(int))!=sizeof(int)){
				printf("\nError to write file.");
				exit(1);
			}
		}
		close(df);
	}
	return 0;
}