#include <stdio.h>
#include <string.h>

void printall(char *string){
	char instring[510]="hello you stupid jew";
	printf("\nenter first one\n");
	fgets(instring,510,stdin);
	printf("%scat",instring);
	char *args[205];
	char *tokenchar = strtok(instring," "); 
	for(int i = 0;i<204;i++){
		if(tokenchar == NULL || strcmp(tokenchar,"\n") ==0){
			break;
		}
		else{
		printf("reading %s\n",instring);
		printf("%s\n",tokenchar);
		args[i] = tokenchar;
		tokenchar =strtok(NULL," ");
		}
	}
	for(int i = 0;i<204;i++){
		if(args[i] ==NULL) break;
		printf("%s\n",args[i]);
	}
}

int main(int arg, char **arc){
	char *hi ="hello satan"; 
	printall(hi);
	return 0; 
}
