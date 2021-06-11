/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

Proceso Pares e Impares
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

//Prototipos
void clean();

int main(int argc, char const *argv[])
{
	int num_pares[10],num_impares[10],*p_num,df_1,df_2,i;
	char dir1[]={"num1.dat"},dir2[]={"num2.dat"};
	pid_t pid_1,pid_2;

	df_1=creat(dir1,0777); //creamos archivo Pares
	df_2=creat(dir2,0777); //creamos archivo Impares

	pid_1=fork(); //Creamos un proceso hijo

	if(pid_1>0){ //Padre
		sleep(30);

		df_1=open(dir1,0);
		df_2=open(dir2,0);

		if (read(df_1,num_pares,sizeof(num_pares))!=sizeof(num_pares)){
			printf("\nError to read file.");
			exit(1);
		}
		if (read(df_2,num_impares,sizeof(num_impares))!=sizeof(num_impares)){
			printf("\nError to read file.");
			exit(1);
		}

		for (i=0; i<10;i++)
		{
			printf("\n%d.- %d + %d = %d",i+1,num_pares[i],num_impares[i],(num_pares[i]+num_impares[i]));
		}
		close(df_1);
		close(df_2);
	}

	if(pid_1==0){ //Hijo

		pid_2=fork();
		if(pid_2>0){ //Pares

			df_1=open(dir1,1);
			//clean();
			for (p_num=num_pares, i=0; i<10;p_num++,i++)
			{
				clean();
				printf("\nInsert %d-Par number",i+1);
				scanf("%d",p_num);
				write(df_1,p_num,sizeof(p_num)); //Escribimos en el archivo
			}
			close(df_1);
		}
		if(pid_2==0){ //Impares

			df_2=open(dir2,1);
			//clean();
			for (p_num=num_impares, i=0; i<10;p_num++,i++)
			{
				clean();
				printf("\nInsert %d-Impar number",i+1);
				scanf("%d",p_num);
				write(df_2,p_num,sizeof(p_num)); //Escribimos en el archivo
			}
			close(df_2);
		}
	}

	return 0;
}

void clean(){
	int c;
	while((c=getchar()) != '\n' && c!=EOF); //Limpiamos buffer
}