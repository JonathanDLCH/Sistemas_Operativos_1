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
#include <time.h>

//Prototipos
void clean();

int main(int argc, char const *argv[])
{
	int num_pares[10],num_impares[10],*p_num1,*p_num2,df_1,df_2,i,par,impar;
	char dir1[]={"num1.dat"},dir2[]={"num2.dat"};
	pid_t pid_1,pid_2;
	time_t t; //Variable para funcion random
	srand((unsigned) time(&t));	//evita numeros iguales en cada compilacion

	df_1=creat(dir1,0777); //creamos archivo Pares
	df_2=creat(dir2,0777); //creamos archivo Impares

	pid_1=fork(); //Creamos un proceso hijo

	if(pid_1>0){ //Padre
		sleep(5);

		df_1=open(dir1,0);
		df_2=open(dir2,0);
/*
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
		}*/

		for (i=0; i<10;i++){
			read(df_1, &par, sizeof(int));
			read(df_2, &impar, sizeof(int));
			printf("\n%d.- %d + %d = %d",i+1,par,impar,(par+impar));
		}

		close(df_1);
		close(df_2);
	}

	if(pid_1==0){ //Hijo

		pid_2=fork();
		if(pid_2>0){ //Pares

			df_1=open(dir1,1);/*
			for (p_num1=num_pares, i=0; i<10;p_num1++,i++)
			{
				do{
					par=rand()%100;
				}while(par%2!=0 && par!=0);
				printf("\n%d-Par number: %d",i+1,par);
				*p_num1=par;
				write(df_1,p_num1,sizeof(p_num1)); //Escribimos en el archivo
			}*/
			for (i=0; i<10;i++)
			{
				do{
					num_pares[i]=rand()%100;
				}while(num_pares[i]%2!=0 && num_pares[i]!=0);
				printf("\n%d-Par number: %d",i+1,num_pares[i]);
				write(df_1,atoi(num_pares[i]),sizeof(int)); //Escribimos en el archivo
			}
			close(df_1);
		}
		if(pid_2==0){ //Impares

			df_2=open(dir2,1);/*
			for (p_num2=num_impares, i=0; i<10;p_num2++,i++)
			{
				do{
					impar=rand()%100;
				}while(impar%2==0);
				printf("\n%d-Impar number: %d",i+1,impar);
				*p_num2=impar;
				write(df_2,p_num2,sizeof(p_num2)); //Escribimos en el archivo
			}*/
			for (i=0; i<10;i++)
			{
				do{
					num_impares[i]=rand()%100;
				}while(num_impares[i]%2!=0 && num_impares[i]!=0);
				printf("\n%d-Impar number: %d",i+1,num_impares[i]);
				write(df_1,atoi(num_impares[i]),sizeof(int)); //Escribimos en el archivo
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