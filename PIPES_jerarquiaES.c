/*
FCC-BUAP
Jonathan De La Cruz Huerta 201731754

Sistemas Operativos 1

PIPES:
Jerarquia de Procesos
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void dri1();

pid_t idgroup;

int main(int argc, char  *argv[]){
	pid_t pid_R,pid_M,pid_L,pid_Q,pid_Z,pid_A,pid_W,pid_K,pid_S,pid_B,pid_D,pid_T,pid_F,pid_E;
	int fd[2],i=1,j=2;

	pipe(fd);

	pid_R=fork();
	if(pid_R>0){ //R
		printf("\nR:%d \tPadre:%d",getpid(),getppid());
		

		struct sigaction s;
		s.sa_handler=dri1;
		sigemptyset(&s.sa_mask);
		s.sa_flags=0;
		sigaddset(&s.sa_mask,SIGKILL);
		sigaction(SIGALRM,&s,NULL);

		

		pid_L=fork();
		if(pid_L==0){ //L

			pid_A=fork();
			
			if(pid_A>0){


				pid_K=fork();
				if(pid_K>0){// L es papa

					pid_W=fork();
					if(pid_W>0){ //L

						printf("\nL:%d \tPadre:%d",getpid(),getppid());
			
						while(1){
							printf("\nSoy L escribiendo: %d",i);
							write(fd[1],&i,sizeof(int));
						}

					}
					
					if(pid_W==0){ //W

						pid_D=fork();
						if(pid_D>0){ //W es papa

							pid_B=fork();
							if(pid_B>0){ //W es papa
								printf("\nW:%d \tPadre:%d",getpid(),getppid());
						
								while(1){
									printf("\nSoy W leyendo: %d",i);
									read(fd[0],&j,sizeof(int));
								}

							}

							if(pid_B==0){ //B
								printf("\nB:%d \tPadre:%d",getpid(),getppid());
								
								while(1){
									printf("\nSoy B leyendo: %d",i);
									read(fd[0],&j,sizeof(int));
								}

							}
						}
						
						if(pid_D==0){ //D

							pid_E=fork();
							if(pid_E>0){// D es papa

								pid_F=fork();
								if(pid_F>0){ //D es papa
									printf("\nD:%d \tPadre:%d",getpid(),getppid());
							
									while(1){
										printf("\nSoy D escribiendo: %d",i);
										write(fd[1],&i,sizeof(int));
									}

								}
								if(pid_F==0){ //F
									printf("\nF:%d \tPadre:%d",getpid(),getppid());
									
									while(1){
										printf("\nSoy F escribiendo: %d",i);
										write(fd[1],&i,sizeof(int));
									}

								}
							}

							if(pid_E==0){ //E
								printf("\nE:%d \tPadre:%d",getpid(),getppid());
								
								while(1){
									printf("\nSoy E escribiendo: %d",i);
									write(fd[1],&i,sizeof(int));
								}

							}
						}
					}
				}
				if(pid_K==0){ //K
					printf("\nK:%d \tPadre:%d",getpid(),getppid());
					
					while(1){
						printf("\nSoy K leyendo: %d",i);
						read(fd[0],&j,sizeof(int));
					}

				}
			}
			if(pid_A==0){ //A
				printf("\nA:%d \tPadre:%d",getpid(),getppid());
				
				while(1){
					printf("\nSoy A escribiendo: %d",i);
					write(fd[1],&i,sizeof(int));
				}

			}
		}
		alarm(5);
		pause();
	}

	if(pid_R==0){

		pid_M=fork();
		if(pid_M>0){ //M

			pid_Z=fork();
			if(pid_Z>0){ //M
				printf("\nM:%d \tPadre:%d",getpid(),getppid());
				
				while(1){
					printf("\nSoy M escribiendo: %d",i);
					write(fd[1],&i,sizeof(int));
				}
			}
			

			
			if(pid_Z==0){ //Z

				pid_S=fork();
				if(pid_S>0){ //Z
					printf("\nZ:%d \tPadre:%d",getpid(),getppid());
					
					while(1){
						printf("\nSoy Z leyendo: %d",i);
						read(fd[0],&j,sizeof(int));
					}
				}
				
				if(pid_S==0){ //S

					pid_T=fork();
					if(pid_T>0){
						printf("\nS:%d \tPadre:%d",getpid(),getppid());
						
						while(1){
							printf("\nSoy S leyendo: %d",i);
							read(fd[0],&j,sizeof(int));
						}
					}
					
					if(pid_T==0){ //T
						printf("\nT:%d \tPadre:%d",getpid(),getppid());
						
						while(1){
							printf("\nSoy T leyendo: %d",i);
							read(fd[0],&j,sizeof(int));
						}

					}
				}
			}
		}
		if(pid_M==0){ //Q
			printf("\nQ:%d \tPadre:%d",getpid(),getppid());

			while(1){
				printf("\nSoy Q leyendo: %d",i);
				read(fd[0],&j,sizeof(int));
			}

		}
	}
	return 0;
}

void dri1(){
	kill(idgroup,SIGKILL);
}