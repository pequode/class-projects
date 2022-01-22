#include <stdio.h>
// use bash comand man for documentation 
// man man gives documentation for man pages
// turn on compiler warrings 
// test programs with valgrind or sanitizers 
// use flag -std=c99

int add(int x,int y){
	return x+y;
}

int main(){
	int k = add(5,6);
	printf("goat\n");
	printf("%d\n",k);
	return 0; 
}
