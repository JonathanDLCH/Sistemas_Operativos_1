/*
	BENEMERITA UNIVERSIDAD AUTONOMA DE PUEBLA
	Sistemas Operativos 1

	Modulo de uso de semaforos.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_RESOURCE_MAX 1 //Valor inicial de todo semaforo

void opensem(int *sid,key_t key);
void createsem(int *sid,key_t key,int members);
void locksem(int sid,int member);
void unlocksem(int sid,int member);
void removesem(int sid);
unsigned short get_member_count(int sid);
int getval(int sid,int member);
void dispval(int sid,int member);
void changemode(int sid,char *mode);
void usage(void);

int main(int argc, char *argv[]){

	key_t key;
	int semset_id;

	if(argc == 1){
		usage();
	}
	key=ftok(".",'s');

	switch(tolower(argv[1][0])){
		case 'c':
				if(argc!=3){
					usage();
				}
				createsem(&semset_id,key,atoi(argv[2]));
				break;
		case 'b':
				if (argc!=3){
					usage();
				}
				opensem(&semset_id,key);
				locksem(semset_id,atoi(argv[2]));
				break;
		case 'd':
				if(argc!=3){
					usage();
				}
				opensem(&semset_id,key);
				unlocksem(semset_id,atoi(argv[2]));
				break;
		case 'b':
				opensem(&semset_id,key);
				removesem(semset_id);
				break;
		case 'm':
				opensem(&semset_id,key);
				changemode(semset_id,argv[2]);
				break;
		default: usage();
	}

	return 0;
}

void opensem(int *sid,key_t key){
	//Abrir (no crear) el conjunto de semaforos
	if((*sid=semget(key,0,0666))==-1){
		printf("No existe el conjunto de semaforos!\n");
		exit(-1);
	}
}

void createsem(int *sid,key_t key,int members){
	int cntr;
	union semun semopts;

	if(members>SEMMSL){
		printf("Lo siento: el numero maximo de semaforos es: %d\n",SEMMSL);
		exit(-1);
	}

	printf("Intentando crear un conjunto de %d miembros\n",members);
	if((*sid=semget(key,members,IPC_CREAT|IPC_EXCL|0666))==-1){
		fprintf(stderr, "El conjunto ya existe!\n" );
		exit(-1);
	}

	semopts.val= SEM_RESOURCE_MAX;

	for(cntr=0;cntr<members;cntr++){ //iniciamos todos los miembros(puede hacerse con SETALL)
		semctl(*sid,cntr,SETVAL,semopts);
	}
}

void locksem(int sid, int member){
	struct setbuf sem_lock={0,-1,IPC_NOWAIT};

	if(member<0 || member>(get_member_count(sid)-1)){
		fprintf(stderr, "miembro %d fuera de rango\n",member);
	}

	if(!getval(sid,member)){
		fprintf(stderr, "Recursos del semaforo agotados(No bloqueo)!\n");
		exit(-1);
	}

	sem_lock.sem_num=member;

	if((semop(sid,&sem_lock,1))==-1){
		fprintf(stderr, "Fallo en bloqueo\n");
		exit(-1);
	}else{
		printf("Recursos decrementados en 1 (bloqueo)\n");
	}

	dispval(sid,member);
}

void unlocksem(int sid,int member){
	struct sembuf sem_unlock={member,1,IPC_NOWAIT};
	int semval;

	if(member<0 || member>(get_member_count(sid)-1)){
		fprintf(stderr, "miembro %d fuera de rango\n",member );
	}

	//Esta bloqueado?
	semval=getval(sid,member);
	if (semval == SEM_RESOURCE_MAX){
		fprintf(stderr,"semaforo no bloqueado!\n");
		exit(-1);
	}

	sem_unlock.sem_num=member;

	//Intentamos desbloquear
	if((semop(sid,&sem_unlock,1))==-1){
		fprintf(stderr, "Fallo en desbloqueo\n");
		exit(-1);
	}else{
		printf("Recurso incrementados en 1 (desbloqueo)\n");
	}
	dispval(sid,member);
}

void removesem(int sid){
	semctl(sid,0,IPC_RMID,0);
	printf("Semaforo borrado\n");
}

unsigned short get_member_count(int sid){
	union semun semopts;
	struct semid_ds mysemds;

	semopts.buf=&mysemds;

	//Devolver numero de miembros
	return(semopts.buf->sem_nsems);
}

int getval(int sid, int member){
	int semval;

	semval=semctl(sid,member,GETVAL,0);
	return(semval);
}

void changemode(int sid,char *mode){
	int rc;
	union semun semopts;
	struct semid_ds mysemds;

	//Obtener valores de la estructura interna
	semopts.buf=&mysemds;

	rc=semctl(sid,0,IPC_STAT,semopts);

	if(rc==-1){
		perror("semctl");
		exit(-1);
	}

	printf("Permisos antiguos: %o\n",semopts.buf->sem_perm.mode );

	//cambair los permisos
	sscanf(mode,"%ho",&semopts.buf->sem_perm.mode);

	//Actualizar estructura interna
	semctl(sid,0,IPC_SET,semopts);

	printf("Actualizando...\n");
}

void dispval(int sid,int member){
	int semval;

	semval=semctl(sid,member,GETVAL,0);
	printf("El semval del miembro %d es %d\n",member,semval);
}

void usage(void){
	fprintf(stderr, "Semtool-Utilidad de manejo de semaforos\n");
	fprintf(stderr, "\nUSAGE: semtool (c)rear <cuantos>\n");
	fprintf(stderr, "\n               (b)loquear <sem #>\n");
	fprintf(stderr, "\n               (d)esbloquear <sem #>\n");
	fprintf(stderr, "\n               (b)orrar\n");
	fprintf(stderr, "\n               (m)odo <modo>\n");
	exit(0);
}