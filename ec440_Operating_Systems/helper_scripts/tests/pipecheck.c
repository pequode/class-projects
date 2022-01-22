# include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
// this fucntion will pipe two comands together 
#define STDIN 0
#define STDOUT 1

int pipes(int npipes){
	/*
	int **fds= (int **)malloc(npipes * sizeof(int *)); 
	for (int i =0;i<npipes;i++){
		 fds[i] = (int *)malloc(2* sizeof(int)); 
	}
	int res;
	pid_t = pid;
	for(int i=0;i<npipes;i++){
		res = pipe(fds[i])
		/// need to pipe at end 
		/// need to use just on array of fd 
		// reassign the fd at the end 
		// leave 5 hours to merge all the "functionality"


		if(res !=0) perror("error in the pipe\n");
		pid = fork()
		if(i == npipes-1){
			printf("I am the last process my pid is%d\n",getpid());			
			if(pid>0){
				// parrent does the control stuff still
				waitpid(pid);
				for (int j = 0; j<npipes;j++){
					free(fds[j]);
				}
				free(fds);
				break;
			}else if(pid ==0){
			//child
				close(fds[i][1]);
				close(STDIN);
				dup(
			}
			else{
				perror("somthing crapped out");
			}
		}
		else if(i == 0){
			printf("I am the first process my pid is %d\n",getpid());
			if(pid>0){
				// parrent does all the control stuff 
				waitpid(pid);
			}
			else if(pid ==0){
				//child does exec shit 
				close(fds[i][0]);
				close(STDOUT);
				dup(fds[i][1]);
				close(fds[i][1]);
				execlp("ls","ls",NULL);
				perror("error exec craped out");
			}
		}
		else{	
			printf("I am the %dth proccess my pid is%d\n",i,getpid());
		}
	}*/
	return 1;
}
// for n pipes 
// pipe[0] has leaves stdin open
// pipe[i] has closed both stdin and out and replaced them with a new fd 
// pipe[n]  leaves stdout open









int main (){
	int len, res;
	char sbuffer[256];
	char rbuffer[256];
	int pipefd[2];
	//printf("\n\n\t%d\n",pipes(10));
	pid_t pid[2];
	res = pipe(pipefd);
	if (res !=0){perror("error in pipe():\n");}
	pid[0] = fork();
	printf("fork Successful");
	int status;
	if(pid[0]>0){
		// parrent 
		waitpid(pid[0],&status,0);
		printf("par pid = %d child pid = %d\n",getpid(), pid[0]);
		pid[1] = fork();
		if (pid[1]>0){
		printf("\nhello from the second parrent");
		waitpid(pid[1],&status,0);
		//close(pipefd[1]);
		//close(STDIN);
		//dup(pipefd[0]);
		close(pipefd[0]);
		execlp("wc","wc",NULL);
		printf("error");
		}else{
			printf("hello from the second child\n");
			close(STDIN);
			//close(STDOUT);
			dup(pipefd[0]);
			close(pipefd[1]);
			dup(STDOUT);
			//dup(pipefd[1]);
			printf("and here");
			//close(pipefd[0]);
			//close(pipefd[1]);
			execlp("wc","wc",NULL);
			exit(42);
			printf("\nerror\n");
		}
	}
	else if(pid[0] ==0) {
	// child
	 	//close(pipefd[0]);
		printf("\ngotHere\n");
		close(STDOUT);
		dup(pipefd[1]);
		//close(pipefd[1]);
		//printf("\nchild got to here\n");
		execlp("ls","ls",NULL);
		printf("error");
		exit(42);
	}
	else{
		printf("error");
	}
	return 0; 
}
