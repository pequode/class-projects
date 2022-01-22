#include <unistd.h>
#include <sys/types.h> 
#include <stdio.h>
int main(){
	if (fork()==0){
		printf("hello from the child\n starting ls\n");
		execlp("ls","ls",NULL);
	}
	else{
		printf("\nhello from the parrent\n");
	}
	return 0; 
}

