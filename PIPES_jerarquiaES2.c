/*
Programa que tiene jerarquia de procesos y usa pipe
R: Temporiza a los procesos por 5 segundos
M,L,A,D,F,E: Son procesos escritores
Q,Z,S,T,W,K,B: son procesos lectores
(Todos los procesos son infinitos)
*/

#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
pid_t idgrupo;

void manejador(){
	kill(idgrupo,SIGKILL);
}

void main(int argc,char *argv[]){
	//atributos
	pid_t pid,pid2,pid3,pid4,pid5,pid6,pid7,pid8,pid9,pid10,pid11,pid12,pid13;
	int fd[2],i;
	int a,b,c,d,e,f,g,r,n,x,y,z,k;
	pipe(fd);
	pid=fork();
	//desarrollo
	if(pid>0){//proceso R
	   pid2=fork();
	   if(pid2>0){//proceso R
		struct sigaction s;
		s.sa_handler=manejador;
		sigemptyset(&s.sa_mask);
		s.sa_flags=0;
		sigaction(SIGALRM,&s,NULL);
		alarm(5);
		pause();
	   }
	   if(pid2==0){//proceso L
	      idgrupo=getpgid(pid2);
	      pid3=fork();
	      if(pid3>0){//proceso L
	         pid4=fork();
		 if(pid4>0){//proceso L
		    pid5=fork();
		    if(pid5>0){//proceso L
		       n=getpid();
		       //id[0]=n;
		       for(;;){
			printf("Soy L escribo: %d\n",n);
			write(fd[1],&n,sizeof(int));
		       }
		    }
		    if(pid5==0){//proceso K
		       //id[1]=getpid();
		       for(;;){
			  read(fd[0],&f,sizeof(int));
			  printf("Soy k leo: %d\n",f);
		       }
		    }
		 }
		 if(pid4==0){//proceso W
		    pid6=fork();
		    if(pid6>0){//proceso W
			pid7=fork();
			if(pid7>0){//proceso W
			   //id[2]=getpid();
			   for(;;){
			     read(fd[0],&e,sizeof(int));
			     printf("Soy W leo: %d\n",e);
			   }
			}
			if(pid7==0){//procso D
			   pid8=fork();
			   if(pid8>0){//proceso D
			      pid9=fork();
			      if(pid9>0){//proceso D
				//id[3]=getpid();
				x=getpid();
				for(;;){
				   printf("Soy D escribo: %d\n",x);
				   write(fd[1],&x,sizeof(int));
				}
			      }
			      if(pid9==0){//proceso E
				z=getpid();
				//id[4]=z;
				for(;;){
				   printf("Soy E escribo: %d\n",z);
				   write(fd[1],&z,sizeof(int));
				}
			      }
			   }
			   if(pid8==0){//proceso F
//			      id[5]=getpid();
			      y=getpid();
			      for(;;){
				printf("Soy F escribo: %d\n",y);
				write(fd[1],&y,sizeof(int));
			      }
			   }
			}
		    }
		    if(pid6==0){//proceso B
			//id[6]=getpid();
			for(;;){
			    read(fd[0],&g,sizeof(int));
			    printf("Soy B leo: %d\n",g);
			}
		    }
		 }
	      }
	      if(pid3==0){//proceso A
		r=getpid();
		//id[7]=r;
		for(;;){
		   printf("Soy A escribo: %d\n",r);
		   write(fd[1],&r,sizeof(int));
		}
	      }
	   }
	}
	if(pid==0){//proceso M
	   pid10=fork();
	   if(pid10>0){//proceso M
	      pid11=fork();
	      if(pid11>0){//proceso M
		i=getpid();
		//id[8]=i;
		for(;;){
		   printf("Soy M escribo: %d\n",i);
		   write(fd[1],&i,sizeof(int));
		}
	      }
	      if(pid11==0){//proceso Z
		 pid12=fork();
		 if(pid12>0){//proceso Z
		    //id[9]=getpid();
		    for(;;){
		      read(fd[0],&b,sizeof(int));
		      printf("Soy Z leo: %d\n",b);
		    }
		 }
		 if(pid12==0){//proceso S
		    pid13=fork();
		    if(pid13>0){//proceso S
			//id[10]=getpid();
			for(;;){
			   read(fd[0],&c,sizeof(int));
			   printf("Soy S leo: %d\n",c);
			}
		    }
		    if(pid13==0){//proceso T
		       //id[11]=getpid();
		       for(;;){
			  read(fd[0],&d,sizeof(int));
			  printf("Soy T leo: %d\n",d);
		       }
		    }
		 }
	      }
	   }
	   if(pid10==0){//proceso Q
	      //id[12]=getpid();
	      for(;;){
	         read(fd[0],&a,sizeof(int));
		 printf("Soy Q leo: %d\n",a);
	      }
	   }
	}
}//fin del main

