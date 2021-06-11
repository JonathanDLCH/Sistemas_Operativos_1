/*
Programa que simulara un banco y tendrá un menú:
1. Dar de alta un cliente
2. Dar de baja un cliente
3. Consultar
4. Salir

Contara con un archivo que guarde la información de cada cliente y este será
BD.dat
Para ir guardando la información de los clientes usaremos una estructura

Proyecto Sistemas Operativos 1
Christiam Alberto Parraguirre Lagunes
Jonathan De la Cruz Huerta
28/11/19 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

struct cliente{
   char nombre[50];
   char direccion[50];
   int cuenta;
   int cantidad;
};

int altaCliente(int df);
void bajaCliente(int df);
int consulta();
void busquedaNombre(char nombre[],int df);
void busquedaCuenta(int cuenta,int df);
void mostrarusuarios(int df);
void openDataBase(int df);

void titulo();
void despedida();

void main(int argc,char *argv[]){
	//atributos
	int op,cb,df;
	char dir[]={"BD.dat"};

	df=creat(dir,0777); //Creamos la base de datos

	do{
		system("clear");
		titulo();
		printf("\n1.- Alta de cliente\n");
		printf("2.- Baja de cliente\n");
		printf("3.- Consulta de cliente\n");
		printf("4.- Salir\n");
		printf("Introduzca el nombre de la operación a realizar: ");
		scanf("%d",&op);
		while((cb=getchar()) != '\n' && cb!=EOF); //Vacia el buffer de manera correcta
		system("clear");

		switch(op){
			case 1:
				if(altaCliente(df)==0){
					printf("Creacion de cliente fallida.\n");
				}else{
					printf("Se creo la cuenta.\n");
				}
				break;
			case 2:
				bajaCliente(df);
				break;
			case 3:
				mostrarusuarios(df);
				break;
			case 4:
				despedida();
				break;
			default:
				printf("Escoga una opción del menú\n");
		}//fin del switch
		close(df);
	}while(op!=4);
}//fin del main

int altaCliente(int df){

	struct cliente miCliente;
	int confirmar,cb;
	openDataBase(df);
	
	printf("Ingrese los siguientes datos\n");
	printf("Titular de tarjeta: ");
	fgets(miCliente.nombre,50,stdin);
	while(miCliente.nombre==NULL || miCliente.nombre[0]=='\n'){
	   printf("Ingrese un nombre valido\n");
	   fgets(miCliente.nombre,50,stdin);
	}
	printf("Número de cuenta: ");
	scanf("%d",&miCliente.cuenta);
	printf("Cantidad inicial: $");
	scanf("%d",&miCliente.cantidad);
	while(miCliente.cantidad<0){
		printf("Ingrese un valor de monto positivo: $");
		scanf("%d",&miCliente.cantidad);
	}
	while((cb=getchar()) != '\n' && cb!=EOF); //Vacia el buffer de manera correcta
	printf("Direccion: ");
	while(fgets(miCliente.direccion,50,stdin)==NULL){
	   printf("Ingrese un nombre valido\n");
	   fgets(miCliente.direccion,50,stdin);
	}

	system("clear");
	printf("Datos de Cuenta-VERIFICACIÓN:\n");
	printf("Nombre: %s",miCliente.nombre);
	printf("Direccion: %s",miCliente.direccion);
	printf("Número de cuenta: %d\n",miCliente.cuenta);
	printf("Monto inicial: $%d\n",miCliente.cantidad);

	printf("1)Guardar y Salir\n0)Salir sin Guardar\n");
	scanf("%d",&confirmar);
	if(confirmar==1){ //guardamos la base de datos
		if(write(df,&miCliente,sizeof(struct cliente))==-1){
			perror("Error al guardar cliente");
		}
	}
	close(df);
	return confirmar;
}//fin de alta cliente

void bajaCliente(int df){
	int cuenta,opcion;
	char nombre[50];

	printf("Seleccione opcion para dar Baja:\n");
	printf("0)Regresar\n1)Nombre\n2)Numero de cuenta\n");
	scanf("%d",&opcion);
	switch(opcion){
		case 0:
			printf("Regresando..\n");
			break;
		case 1:
			printf("Titular de tarjeta: ");
			fgets(nombre,50,stdin);
			while(nombre==NULL || nombre[0]=='\n'){
			   printf("Ingrese un nombre valido\n");
			   fgets(nombre,50,stdin);
			}
			busquedaNombre(nombre,df);
			break;
		case 2:
			printf("Número de cuenta: ");
			scanf("%d",&cuenta);
			while(cuenta==0){
				printf("Ingrese un Número de cuenta valido: ");
				scanf("%d",&cuenta);
			}
			busquedaCuenta(cuenta,df);
			break;
		default:
			printf("Escoga una opción del menú\n");
	}
}

void busquedaNombre(char nombre[],int df){
	struct cliente clientesRegistrados[200];
	struct cliente clientesActuales[500];
	int i=0,flag=0,df2,contador=0;
	char dir[]={"BD.dat"};

	while(read(df,&clientesRegistrados[i],sizeof(struct cliente))>0){
		contador++;
		if(clientesRegistrados[i].nombre==nombre){
			flag=1;
			break;
		}else{
			clientesActuales[i]=clientesRegistrados[i];
		}
		i++;
	}
	if(flag==0){
		printf("No se encontraron coincidencias.\n");
	}else{
		df2=creat(dir,2);
		openDataBase(df2);
		for(i=0;i<contador;i++){
			if(write(df2,&clientesActuales[i],sizeof(struct cliente))==-1){
				perror("Error al guardar cliente");
			}
		}
	}
	close(df);
	close(df2);
}

void busquedaCuenta(int cuenta,int df){
	struct cliente clientesRegistrados[200];
	struct cliente clientesActuales[500];
	int i=0,flag=0,df2,contador=0;
	char dir[]={"BD.dat"};

	while(read(df,&clientesRegistrados[i],sizeof(struct cliente))>0){
		contador++;
		if(clientesRegistrados[i].cuenta==cuenta){
			flag=1;
			break;
		}else{
			clientesActuales[i]=clientesRegistrados[i];
		}
		i++;
	}
	if(flag==0){
		printf("No se encontraron coincidencias.\n");
	}else{
		df2=creat(dir,2);
		openDataBase(df2);
		for(i=0;i<contador;i++){
			if(write(df2,&clientesActuales[i],sizeof(struct cliente))==-1){
				perror("Error al guardar cliente");
			}
		}
	}
}
/*
struct cliente busquedaCuenta(int cuenta,int df){
	struct cliente clientesRegistrados[200];
	int i=0,flag=0;

	while(read(df,&clientesRegistrados[i],sizeof(struct cliente))>0){
		if(clientesRegistrados[i].cuenta==cuenta){
			return clientesRegistrados[i];
			flag=1;
			break;
		}
	}
	if(flag==0){
		printf("No se encontraron coincidencias.\n");
	}
}
*/

void mostrarusuarios(int df){
	struct cliente clienteRegistrado;
	char next;

	while(read(df,&clienteRegistrado,sizeof(struct cliente))>0){
		printf("\nDatos del cliente\n");
		printf("Nombre: %s\n",clienteRegistrado.nombre);
		printf("Cuenta: %d\n",clienteRegistrado.cuenta);
		printf("Cantidad: %d\n",clienteRegistrado.cantidad);
		printf("Direccion: %s\n",clienteRegistrado.direccion);
	}
	printf("Presione cualquier tecla para continuar\n");
	scanf("%c",&next);
}

void openDataBase(int df){
	char dir[]={"BD.dat"};

	df=open(dir,2);
	if(df==-1){
		perror("Error al abrir la base de datos.");
		exit(-1);
	}
}//fin de alta cliente

void titulo(){
	printf("┏━━━┓┏━━━┓┏━┓ ┏┓┏━━━┓┏━━━┓\n");
	printf("┃┏━┓┃┃┏━┓┃┃┃┗┓┃┃┃┏━┓┃┃┏━┓┃\n");
	printf("┃┗━┛┃┃┃ ┃┃┃┏┓┗┛┃┃┃ ┗┛┃┃ ┃┃\n");
	printf("┃┏━┓┃┃┗━┛┃┃┃┗┓┃┃┃┃ ┏┓┃┃ ┃┃\n");
	printf("┃┗━┛┃┃┏━┓┃┃┃ ┃┃┃┃┗━┛┃┃┗━┛┃\n");
	printf("┗━━━┛┗┛ ┗┛┗┛ ┗━┛┗━━━┛┗━━━┛\n");
	printf("//////////////////////////\n");/*
┏━━┓┏┓╋┏┳━━━┳━━━┓
┃┏┓┃┃┃╋┃┃┏━┓┃┏━┓┃
┃┗┛┗┫┃╋┃┃┃╋┃┃┗━┛┃
┃┏━┓┃┃╋┃┃┗━┛┃┏━━┛
┃┗━┛┃┗━┛┃┏━┓┃┃
┗━━━┻━━━┻┛╋┗┻┛
*/
}

void despedida(){
	printf("┏┓┏━━━┓┏━━━┓┏━━━┓┏━━━┓┏━━┓┏━━━┓┏━━━┓  ┏┓  ┏┓┏┓ ┏┓┏━━━┓┏┓   ┏┓  ┏┓┏━━━┓  ┏━━━┓┏━━━┓┏━━━┓┏━┓ ┏┓┏━━━━┓┏━━━┓┏┓\n");
	printf("┗┛┃┏━┓┃┃┏━┓┃┃┏━┓┃┃┏━┓┃┗┫┣┛┃┏━┓┃┃┏━┓┃  ┃┗┓┏┛┃┃┃ ┃┃┃┏━━┛┃┃   ┃┗┓┏┛┃┃┏━┓┃  ┃┏━┓┃┃┏━┓┃┃┏━┓┃┃┃┗┓┃┃┃┏┓┏┓┃┃┏━┓┃┃┃\n");
	printf("┏┓┃┃ ┗┛┃┗━┛┃┃┃ ┃┃┃┃ ┗┛ ┃┃ ┃┃ ┃┃┃┗━━┓  ┗┓┃┃┏┛┃┃ ┃┃┃┗━━┓┃┃   ┗┓┃┃┏┛┃┃ ┃┃  ┃┗━┛┃┃┗━┛┃┃┃ ┃┃┃┏┓┗┛┃┗┛┃┃┗┛┃┃ ┃┃┃┃\n");
	printf("┃┃┃┃┏━┓┃┏┓┏┛┃┗━┛┃┃┃ ┏┓ ┃┃ ┃┗━┛┃┗━━┓┃   ┃┗┛┃ ┃┃ ┃┃┃┏━━┛┃┃ ┏┓ ┃┗┛┃ ┃┗━┛┃  ┃┏━━┛┃┏┓┏┛┃┃ ┃┃┃┃┗┓┃┃  ┃┃  ┃┃ ┃┃┗┛\n");
	printf("┃┃┃┗┻━┃┃┃┃┗┓┃┏━┓┃┃┗━┛┃┏┫┣┓┃┏━┓┃┃┗━┛┃   ┗┓┏┛ ┃┗━┛┃┃┗━━┓┃┗━┛┃ ┗┓┏┛ ┃┏━┓┃  ┃┃   ┃┃┃┗┓┃┗━┛┃┃┃ ┃┃┃  ┃┃  ┃┗━┛┃┏┓\n");
	printf("┗┛┗━━━┛┗┛┗━┛┗┛ ┗┛┗━━━┛┗━━┛┗┛ ┗┛┗━━━┛    ┗┛  ┗━━━┛┗━━━┛┗━━━┛  ┗┛  ┗┛ ┗┛  ┗┛   ┗┛┗━┛┗━━━┛┗┛ ┗━┛  ┗┛  ┗━━━┛┗┛\n");
}