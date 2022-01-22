#include <stdio.h> 
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#define STDIN 0 
#define STDOUT 1

int on = 1;
void print(const char* text){if(on ==1){ printf(text);}}
void format(char *args[205]){
        print("\nmy_shell$");
	char instring[510];
        fgets(instring,510,stdin);
        char *tokenchar = strtok(instring," "); 
	int lasti;
        for(int i = 0;i<204;i++){
		lasti =i;
                if(tokenchar == NULL || strcmp(tokenchar,"\n") ==0){
                        break;
                }
                else{
                args[i] = tokenchar;
                tokenchar =strtok(NULL," ");
                }
        }
	if (lasti>1)args[lasti-1]=NULL;
	//else{args[1]=NULL; printf(args[0]);}
	//return args;
}


int main(int argc, char ** argv){
	pid_t pid;// creates pid for splitting programs  
	// set pid of shell
	if(argc >1){
		if(strcmp(argv[1],"-n")==0)on =0;
		else{
			printf("too Many args or bad format");
		}
	}
	char *linein[205];
	for(int i =0; i<100; i++){
		format(linein);
		//while ((getchar()) != '\n');//flushing the input buffer taken from https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/#:~:text=Using%20%E2%80%9C%20while%20((getchar()),input%20in%20the%20desired%20container.
		if(strcmp(linein[0],"end")==0){
			print("quitting\n");
			exit(42);
			break;
		}
		else{
			pid = fork();
			if(pid==0){
				print("child running\n");
				print(linein[1]);
				execvp(linein[0],NULL);
				print("error");
				exit(666);
				break;
			}
			else if(pid>0){
				wait(NULL);
				//print("\n\nim still kicking\n\n");
			}
			else{
				printf("Error quitting...");
				perror("Error: ");
			}
		}
	}
	return 0;
	// system calls is how you do this 
	// sigaction importatn for hw 1 
	// kill sends any signal to the process 
 	// signal mask change sigal
	// man 7 signal 
	// sigaction
	// dup2 important for pipe part of schell
	// all shell does is tweek fds for different programs
	// impoet bin ls 
	// exec everingthing in the 
}/*
void closeAllPipes(int *fds, int npipes){
        int k = 2*npipes;
        for(int i =0; i<k;i++){
                close(fds[i]);
        }

}
int pipes(int npipes){// help from http://www.cs.loyola.edu/~jglenn/702/S2005/E$
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
                        printf("%d      %d\n",i*2-2,i*2+1);
                        if(i>0){
                                int j;
				printf("fds = %d\n",fds[i*2-2]);
                                if(j = dup2(fds[i*2-2],STDIN)==-1){ printf("err$
                                printf("new j is %d\n",j);
                        }
                        if(i<npipes){
                                int l;
                                printf("fds = %d\n",fds[i*2+1]);
                                if(l = dup2(fds[i*2+1],STDOUT)==-1){ printf("er$
                                //printf("new l is %d\n",l);
                        }
                        //printf("after dup2 = %d:[%d]-[%d]\n",i,fds[i*2],fds[i$
                        closeAllPipes(fds,npipes);
                        //printf("after close = %d:[%d]-[%d]\n",i,fds[i*2],fds[$

                        if(i>0){ execlp("wc","wc",NULL);
                                printf("\nbro");
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
	return 1;
}


*/
