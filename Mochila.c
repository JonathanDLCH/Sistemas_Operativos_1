/*
Proyecto de algoritmos voraces
Problema de la mochila
Christiam Alberto Parraguirre Lagunes
Jonathan De La Cruz Huerta
Análisis y diseño de Algoritmos
*/
#include<stdio.h>
#include<stdlib.h>

struct Objeto{
	char nombre[40];
	int peso;
	int valor;
	int cantidad;
	float valorUnitario;
};

//void Combsort(struct Objeto *Objetos[],int n);

void main(int argc,char *argv[]){

	int n=atoi(argv[1]),weight,cb,n_obj;
	float resultado;
	struct Objeto Objetos[n];

	int factorS,cambio,j;
	struct Objeto ayuda;

	printf("Caracteristicas de los Objetos\n");
	for(int i=0;i<n;i++){
		while((cb=getchar()) != '\n' && cb!=EOF); //Vacia el buffer de manera correcta
		printf("Nombre del Objeto %d\n",i+1);
		fgets(Objetos[i].nombre,40,stdin);
		printf("Peso: (kg)\n"); scanf("%d",&Objetos[i].peso);
		printf("Valor: ($)\n"); scanf("%d",&Objetos[i].valor);
		Objetos[i].valorUnitario=(float)Objetos[i].valor/(float)Objetos[i].peso;
		printf("Valor Unitario: %f\n",Objetos[i].valorUnitario);
		Objetos[i].cantidad=0;
	}

	factorS=n;
	do{
		if((factorS/1.3)>1){
			factorS= (int)(factorS/1.3);
		}else{
			factorS=1;
		}
		cambio=0;
		for (int i = 0; i <(n-factorS); i++)
		{
			j=i+factorS;

			if(Objetos[i].valorUnitario>Objetos[j].valorUnitario){
				ayuda=Objetos[i];
				Objetos[i]=Objetos[j];
				Objetos[j]=ayuda;
				cambio=1;
			}
		}
	}while(factorS!=1 || cambio!=1);
/*
	for (int i=0; i<n; i++){
		printf("Nombre: %s\n",Objetos[i].nombre);
		printf("peso: %d\n",Objetos[i].peso);
		printf("valor: %d\n",Objetos[i].valor);
		printf("valor unitario: %f\n",Objetos[i].valorUnitario);
	}
*/
	do{
		printf("Peso de carga de la mochila: ");
		scanf("%d",&weight); //Peso maximo para llevar
	}while(weight<=0);

	n_obj=n-1;
	while(weight>=0){
		if(n_obj>=0){
			if(weight>=Objetos[n_obj].peso){
				printf("n_obj: %d\n",n_obj);
				Objetos[n_obj].cantidad = weight/Objetos[n_obj].peso;
				resultado = weight%Objetos[n_obj].peso;
				weight=resultado;	
			}
			n_obj--;
			printf("n_obj: %d\n",n_obj);
		}
		printf("hola\n");
	}

	printf("Objetos para llevar:\n");
	for (int i=0; i<n; i++){
		printf("%d %s \n",Objetos[i].cantidad,Objetos[i].nombre);
	}
}
/*
void Combsort(struct Objeto *Objetos[],int n){

	int factorS,cambio,j;
	struct Objeto *ayuda;

	factorS=n;
	do{
		if((factorS/1.3)>1){
			factorS= (int)(factorS/1.3);
		}else{
			factorS=1;
		}
		cambio=0;
		for (int i = 0; i <(n-factorS); i++)
		{
			j=i+factorS;

			if(Objetos[i]->valorUnitario>Objetos[j]->valorUnitario){
				ayuda=Objetos[i];
				Objetos[i]=Objetos[j];
				Objetos[j]=ayuda;
				cambio=1;
			}
		}
	}while(factorS!=1 || cambio!=1);

	for (int i=0; i<n; i++){
		printf("Nombre: %s\n",Objetos[i]->nombre);
		printf("peso: %d\n",Objetos[i]->peso);
		printf("valor: %d\n",Objetos[i]->valor);
		printf("valor unitario: %f\n",Objetos[i]->valorUnitario);
	}
}*/