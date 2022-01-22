#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include"ec440threadsnotBandit.h"

#define THREAD_CNT 3
// waste some time
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
int main(int argc, char **argv) {
	bool cool = true;
	struct cat bill ={10,"bill",cool,'t'};
	
	printf("%s is %d and his gender is %c",bill.name,bill.age,bill.gender);
 	pthread_t threads[THREAD_CNT];
 	int i;
 	unsigned long int cnt = 10000000;
 	//create THRAD_CNT threads
 	for(i = 0; i<THREAD_CNT; i++) {
 		pthread_create(&threads[i], NULL, count, (void *)((i+1)*cnt));
 	}
 //join all threads ... not important for
//proj2
	for(i = 0; i<THREAD_CNT; i++) {
 		pthread_join(threads[i], NULL);
	}
	return 0;
}