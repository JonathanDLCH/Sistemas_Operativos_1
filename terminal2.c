#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>//memoria compartida
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{

int id,id2,n,id3;
key_t key,key2,key3;
int *dato;
char cadena[20],*ptr;


/*OBTIENE CLAVE IPC*/
key=ftok("/tmp/",'s');
key2=ftok("/tmp/",'z');

id=shmget(key,sizeof(cadena),0666);//abre seg. de cadena con su respectiva ruta
id2=shmget(key2,sizeof(int),0666);//abre seg. de id  con su respectiva ruta

ptr=shmat(id,0,0);//Asociacion seg. cadena
dato=shmat(id2,0,0);//Asociacion seg. id


strcpy(cadena,ptr);

printf("CADENA  EN AP %s \n",ptr);
printf("ID EN AP %d \n",*dato);

n=*dato;
printf("ID EN n %d \n",n);

/*OBTIENE EL TAMAÑO DEL ARCHIVO*/
struct stat fileStat;
if(stat(cadena,&fileStat) < 0)
return 1;
long int tam=fileStat.st_size;
printf("Tamaño de archivo %ld bytes\n",tam);

/*CREAR SEGMENTO PARA ARCHIVO*/
key3=ftok("/tmp/",'x');//ruta del nuevo seg. para el archivo

id3=shmget(key3,tam,IPC_CREAT|0666);//crea seg. de archivo con su respectiva  ruta

char *cad=shmat(id3,0,0);//Asociacion seg.de arch.

/*MANEJO DEL ARCHIVO*/
int descriptor;
descriptor=open(cadena,0);

if(descriptor==-1){
printf("ERROR\n");}

else{

printf("EXITOSO\n");
read(descriptor,cad,tam);//guarda el cont del archivo en el segmento
}

/*MANDA LA SEÑAL*/
kill(n,SIGUSR1);




}//fin de main


