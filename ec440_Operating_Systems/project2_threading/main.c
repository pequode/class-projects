
#include"threads.h"
#include<pthread.h>
#define THREAD_CNT 5
jmp_buf buf;
void *count(void *arg) {
	unsigned long int c = (unsigned long int)arg;
 	int i;
	for (i = 0; i < c; i++) {
		if ((i % 1000) == 0) {
		 printf("id: %x cntd to %d of %ld\n",(unsigned int)pthread_self(), i, c);
		}
	}
return arg;
}

void *printCompliments(void *helo){
	long int hello = (long int)helo;
	printf("your number %ld in my book\n",hello);
	int i= 0;
	for(;i<hello;i++)printf("you make me smile\n");
	return helo;
}
int main(int argc, char **argv) {

	
 	pthread_t threads[THREAD_CNT]; 
	unsigned long int cnt = 10000000;
	int i;
	i = 0; 
	for(; i<THREAD_CNT; i++) {
 		pthread_create(&threads[i], NULL, count, (void *)((i+1)*cnt));
 	}

 	count((void *)(10000000*5));
 	printCompliments((void *)10);
 	printSomeThreads();
 	printf("end wrong\n");
	return 0;
}
