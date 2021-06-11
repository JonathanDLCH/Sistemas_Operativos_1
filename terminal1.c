
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>//memoria compartida
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>

void manejador()
{

 printf("RECIBE SEÑAL SIGURS1\n");
}


int main(int argc,char*argv[])
{
int id,id2,*n,id4;
key_t key,key2,key4;
char nombre[20];
char *ptr=NULL;;
pid_t pid;


/*OBTIENE LLAVE*/
key=ftok("/tmp/",'s');//crea segmento para cadena
key2=ftok("/tmp/",'z');//crea segmento para ID

strcpy(nombre,argv[1]);//guarda nombre

printf("NOMBRE %s \n",nombre);
id=shmget(key,sizeof(nombre),IPC_CREAT|0666);//crea  ID  para cadena
id2=shmget(key2,sizeof(int),IPC_CREAT|0666);//crea ID  para pid

ptr=shmat(id,0,0);//Asociacion al seg. de cadena
n=shmat(id2,0,0);//Asociacion al seg. de pid

strcpy(ptr,nombre);
printf("%s \n",ptr);

*n=getpid();
printf("%d \n",*n);

/*ARMA SEÑAL*/
struct sigaction s;
s.sa_handler=manejador;
sigemptyset(&s.sa_mask);
s.sa_flags=0;
sigaction(SIGUSR1,&s,NULL);


pause();
/*MANEJO DE ARCHIVO*/

/*OBTIENE EL TAMAÑO DEL ARCHIVO*/
struct stat fileStat;
if(stat(nombre,&fileStat) < 0)
return 1;
long int tam=fileStat.st_size;
printf("Tamaño de archivo %ld bytes\n",tam);

/*SEGMENTO PARA LEER ARCH*/
key4=ftok("/tmp/",'x');//crea segmento para archivo
id4=shmget(key4,tam,0666);//crea ID de archivo
char *cad=shmat(id4,0,0);//Asociacion seg.de arch.
printf("%s",cad);

shmdt(ptr);//liberar
shmdt(n);//liberar
shmdt(cad);//liberar
shmctl(id4,IPC_RMID,NULL);//el sistema libera el segmento
 


}//fin de main


