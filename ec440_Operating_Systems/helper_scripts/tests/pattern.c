#include <stdio.h> 
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/wait.h>
int main(){
	printf("ok start\n");
	char comand[512]= "ls";
	char comand2 [512] = "-l -t";
	for(int i =0; i<10; i++){
		printf("\nmy_shell$");
		fgets(comand,512,stdin);
		while ((getchar()) != '\n');//flushing the input buffer taken from https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/#:~:text=Using%20%E2%80%9C%20while%20((getchar()),input%20in%20the%20desired%20container.
		if(strcmp(comand,"end")==0){
			printf("quitting\n");
			break;
		}
		else{
			printf(comand);
			if(fork()==0){
				printf("child baby\n");
				execlp(comand,comand,"-l","-t",NULL);
				break;
			}
			else{
				wait();
				printf("\n\nim still kicking\n\n");
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
}
