# include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define STDIN 0
#define STDOUT 1
void closeAllPipes(int *fds, int npipes){
	int k = 2*npipes;
	for(int i =0; i<k;i++){
		close(fds[i]);
	}

}
int pipes(int npipes){// help from http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html
	pid_t pid;
	int *p;
	int *fds = malloc(2*npipes*sizeof(int));
	for(int i =0;i<2*npipes;i++)fds[i]=0;
	for(int i = 0;i<npipes;i++)pipe(fds+i*2);
	for(int i =0; i<2*npipes;i++)printf("%d:%d\n",i,fds[i]);
	for (int i =0;i<npipes;i++){
		//printf("\n%d\n",i);
		pid =fork();
		if (pid == -1)exit(666);
		if(pid == 0){
			printf("\nhello from the child\n");
			printf("%d:[%d]-[%d]\n",i,fds[i*2],fds[i*2+1]);
			printf("%d	%d\n",i*2-2,i*2+1);
			if(i>0){
				int j;
				printf("fds = %d\n",fds[i*2-2]);
				if(j = dup2(fds[i*2-2],STDIN)==-1){ printf("error exit");exit(22);}
				printf("new j is %d\n",j);
			}
			if(i<npipes){
				int l;
				printf("fds = %d\n",fds[i*2+1]);
				if(l = dup2(fds[i*2+1],STDOUT)==-1){ printf("error exit");exit(22);}
				//printf("new l is %d\n",l);
			}
			//printf("after dup2 = %d:[%d]-[%d]\n",i,fds[i*2],fds[i*2+1]);
			closeAllPipes(fds,npipes);
			//printf("after close = %d:[%d]-[%d]\n",i,fds[i*2],fds[i*2+1]);

			if(i>0){ execlp("wc","wc",NULL);
				printf("\nbro fuck");
				exit(43);
			}
			else if (i == 0){
				execlp("ls","ls",NULL);
				printf("\nfuck bro");
				exit(42);
			}
			else{
				printf("\nDarmmit why wont this work!");
			}
			closeAllPipes(fds,npipes);
			exit(42);
		}
		else{
			printf("\nparrent\n");
			//closeAllPipes(fds,npipes);
			wait(p);
		}
	}
	closeAllPipes(fds,npipes);
	wait(p);
	free(fds);
	/*
	for(int i = 0;i<npipes;i++){
		pid = fork();
		if(pid == 0){
			pipe(fds +(2*i));
			close(STDOUT);
			dup(fds[i]);
			if(i>0){
				close(STDIN);
				int k = i-1;
				dup(fds[i-1]);
				execlp("wc","wc",NULL);
			}else{
				printf("first%d",i);
				execlp("ls","ls",NULL);
			}
			close(fds[i]);
		}
		wait(p);
	}*/
//	free(fds);
	return 1;
}
// for n pipes 
// pipe[0] has leaves stdin open
// pipe[i] has closed both stdin and out and replaced them with a new fd 
// pipe[n]  leaves stdout open









int main (){
	int len = pipes(2);
	printf("\nsuccess:%d",len);
	return 0; 
}
