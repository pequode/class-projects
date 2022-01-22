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
int formatBuff( char *in, char *argout[205]){
	print("format testing");
	char *tok = strtok(in, " ");
	for(int i =0;i<206;i++){
		if (tok == NULL)break;
		else{
			printf("reading: \t%s",tok);
			argout[i] = tok; 
			tok = strtok(NULL," ");
		}
	} 
	print("successful");
	return -1;
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

	print("ok start\n");
	char inBuff[513]; 
	for(int i =0; i<10; i++){
		print("\nmy_shell$");
		fgets(inBuff,513,stdin);
		while ((getchar()) != '\n');//flushing the input buffer taken from https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/#:~:text=Using%20%E2%80%9C%20while%20((getchar()),input%20in%20the%20desired%20container.
		char firstcom[33];
		char everthingElse[481];
		formatBuff(inBuff,firstcom,everthingElse);
		if(strcmp(firstcom,"end")==0){
			print("quitting\n");
			break;
		}
		else{
			print(inBuff);
			pid = fork();
			if(pid==0){
				print("child baby\n");
				execvp(firstcom,everthingElse);
				exit(666);
				break;
			}
			else if(pid>0){
				wait(NULL);// need to implement waitpid instead to stop killing & processes 
				print("\n\nim still kicking\n\n");
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
}
