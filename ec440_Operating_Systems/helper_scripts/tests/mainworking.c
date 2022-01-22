
#include"threads.h"
#include<pthread.h>
#define THREAD_CNT 3
jmp_buf buf;
sem_t mutex; 
sem_t full; 
sem_t empty; 
int item =5; 
void *count(void *arg) {
	unsigned long int c = (unsigned long int)arg;
 	int i;
 	c ++;
 	long countsize = 30000000;
	for (i = 0; i <countsize ; i++) {
		if ((i % 1000000) == 0) {
		 printf("id: %x cntd to %d of %ld\n",(unsigned int)pthread_self(), i, countsize);
		}
	}
return (void*)c;
}

void *countFib(void *arg) {
	unsigned long int c = (unsigned long int)arg;
	c ++;
 	unsigned long int one = 1, two=1, temp =0;
 	int i;
 	long countsize = 50000000;
	for (i = 0; i < countsize; i++) {
		temp = two; 
		two += one; 
		one = temp;
		if ((i % 1000000) == 0) {
		 printf("id: %x  fib is%ld\n",(unsigned int)pthread_self(),one);
		}
	}

return (void*)c;
}
void *printCompliments(void *helo){
	long int hello = (long int)helo;
	printf("your number %ld in my book\n",hello);
	int i= 0;
	for(;i<hello;i++)printf("you make me smile\n");
	return helo;
}
void *A(void *helo){
	int i = 0;
	sem_t * mutex = (sem_t *)helo;
	FILE * fid;
	for(;i<10;i++){
		sem_wait(mutex);
		fid = fopen("outputTest.txt","a");
		fprintf(fid, "A got to go\n");
		fclose(fid);
		sem_post(mutex);
	}
	printf("still working on this");
	return (void*)mutex;
}
void *B(void *helo){
	sem_t * mutex = (sem_t *)helo;
	int i = 0;
	FILE * fid;
	for(;i<10;i++){
		sem_wait(mutex);
		fid = fopen("outputTest.txt","a");
		fprintf(fid, "B got to go\n");
		fclose(fid);
		sem_post(mutex);
	}
	printf("still working on this");
	return (void*)mutex;
}
void* thrd(void* arg) // from https://www.geeksforgeeks.org/use-posix-semaphores-c/
{ 
    //wait 
    sem_wait(&mutex); 
    printf("\nEntered..\n"); 
  
    //critical section 
    sleep(4); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&mutex); 
    return arg;
} 
void* producer(void* args) {
    printf("starting producer...\n");
    int i = 0;//count = (int)args,
    for (;i < 10;i++) {
        printf("********prod#%u********Itter:%d\n",(unsigned)pthread_self(), i);
        printf("empty--\n");
        sem_wait(&empty); 
        sem_wait(&mutex); 
        printf("mutex--\n");
        printf("critiacal vvvvvvvvv\n");
        printf("#%d  is adding %d to %d now %d\n", (unsigned)pthread_self(), 1,item, item + 1);
        item++;
        printf("critiacal ^^^^^^^^\n");
        printf("mutex++\n");
        sem_post(&mutex); 
        printf("full++\n");
        sem_post(&full);  
    }
    return args; 
}
void* consumer(void* args) {
    printf("starting consumer...\n");
    int i = 0;//count = (int)args,
    for (;i < 3;i++){
        printf("********con#%u********Itter:%d\n",(unsigned)pthread_self(), i);
        sem_wait(&full); 
        printf("full -- \n");
        sem_wait(&mutex); 
        printf("mutex--\n");

        printf("critiacal vvvvvvvvv\n");
        printf("#%d is taking %d from %d now %d\n", (unsigned)pthread_self(), 1, item,item-1);
        item--;

        printf("critiacal ^^^^^^^^\n");
        printf("mutex++\n");
        sem_post(&mutex); 
        printf("empty ++\n");
        sem_post(&empty); 
    }
    return args;
}
int main(int argc, char **argv) {
    pthread_t prothread, conthread1,conthread2,conthread3;

    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    //pthread_create(&thread, NULL, count,(void *)((2+1)*1000000));
    pthread_create(&conthread1,NULL,consumer,NULL);
    pthread_create(&conthread2,NULL,consumer,NULL);
    pthread_create(&conthread3,NULL,consumer,NULL);
    pthread_create(&prothread,NULL,producer,NULL);
    //pthread_create(&thread2, NULL, count,(void *)((2+1)*1000000));

    //pthread_join(thread,NULL);
    pthread_join(prothread,NULL);
    pthread_join(conthread1,NULL);
    pthread_join(conthread2,NULL);
    pthread_join(conthread3,NULL);
    sem_destroy(&mutex); 
    sem_destroy(&full); 
    sem_destroy(&empty); 



	





 // 	pthread_t threads[THREAD_CNT]; 
	// //unsigned long int cnt = 10000000;
	// int i= 0; 
	// /*
	// for(; i<THREAD_CNT; i++) {
 // 		pthread_create(&threads[i], NULL, count, (void *)((i+1)*cnt));
 // 	}*/
 // 	pthread_create(&threads[i], NULL, count, (void *)(6));
 // 	i++;
 // 	pthread_create(&threads[i], NULL, countFib, (void *)(2));
 // 	i++;
 // 	pthread_create(&threads[i], NULL, count, (void *)(5));
 // 	i++;
 // 	void *v;
 // 	int k; 
 // 	for(i = 0; i<THREAD_CNT; i++) {
 // 		printf("%d exited %d\n",i,pthread_join(threads[i], &v));
 // 		k =i ;
	// }
 // 	printf("in main\n");
 // 	printSomeThreads();
 // 	printf("thread %d exited with value %ld\n",k,(unsigned long int)v);
 	
 // 	printf("end wrong front \n");
	exitAll();
	return 0;
}
// disc notes use sigprocmask to lock and unlock 
//