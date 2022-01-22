
#include"threads.h"
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#define THREAD_CNT 3
jmp_buf buf;
sem_t mutex; 
sem_t mutexfile;
sem_t full; 
sem_t empty; 
sem_t demoSent;
int item =5; 
void *count(void *arg) {
	unsigned long int c = (unsigned long int)arg;
 	int i;
 	c ++;
	for (i = 0; i <c ; i++) {
		if ((i % 1000000) == 0) {
		 printf("id: %x cntd to %d of %ld\n",(unsigned int)pthread_self(), i, c);
		}
	}
return arg;
}
void timeWaster(unsigned long int c ) {
    int i;
    int k=0;
    unsigned long int cd = c*1000000;
    for (i = 0; i <cd ; i++) {
        if ((i % 1000000) == 0) {
         k= k+1;
        }
    }
    if (k <1) printf("Call me ishmale");
}
void *printString(void *arg){
    char * k = (char *)arg;
    int n = strlen(k);
    unsigned long int c = 20;
    int i =0;
    for(i =0;i<n;i++){
        if (k[i] == ' '){
            // sem_wait(&demoSent); 
            printf(" ");
            // sem_post(&demoSent); 
            timeWaster(c);
        }
        else printf("%c",k[i]);
    }
    return arg;
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
	FILE * fid;
	for(;i<10;i++){
		sem_wait(&mutexfile);
		fid = fopen("outputTest.txt","a");
		fprintf(fid, "%s got to go\n",(char *)helo);
		fclose(fid);
		sem_post(&mutexfile);
	}
	printf("still working on this");
	return NULL;
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
// idea to use producer consumer from sildes from justin melvil 
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
    int numberofchars=100/3; 
    char* l1 =  NULL; 
    char* l2= (char *)malloc(numberofchars*sizeof(char));  
    char* l3 = (char *)malloc(numberofchars*sizeof(char)); 
    FILE * fp;

    char * line = NULL;
    size_t len = 0;

    fp = fopen("ScramSent.txt", "r");
    int count =0;
    while ((getline(&line, &len, fp)) != -1) {
        if (count ==0){
            l1 = strdup(line);
        }else if(count ==1){
            l2 = strdup(line);
        }else{
            l3 = strdup(line);
        }
        count++;
    }
    fclose(fp);
    printf("%s\n ",l1);
    printf("%s\n ",l2);
    printf("%s \n\n",l3);


    sem_init(&demoSent, 0, 1);
    pthread_t strings1, strings2,strings3;
    pthread_create(&strings1,NULL,printString,(void *)(l1));
    pthread_create(&strings2,NULL,printString,(void *)(l2));
    pthread_create(&strings3,NULL,printString,(void *)(l3));
    pthread_join(strings1,NULL);
    pthread_join(strings2,NULL);
    pthread_join(strings3,NULL);
    sem_destroy(&demoSent); 

    free(l1);
    free(l2);
    free(l3);
    // real test 
 //    pthread_t prothread, conthread1,conthread2,conthread3,f1,f2,f3;

 //    sem_init(&empty, 0, 10);
 //    sem_init(&mutexfile, 0, 1);
 //    sem_init(&full, 0, 0);
 //    sem_init(&mutex, 0, 1);

 //    pthread_create(&conthread1,NULL,consumer,NULL);
 //    pthread_create(&conthread2,NULL,consumer,NULL);
 //    pthread_create(&conthread3,NULL,consumer,NULL);
 //    pthread_create(&prothread,NULL,producer,NULL);
 //    pthread_create(&f1,NULL,A,(void *)("A"));
 //    pthread_create(&f2,NULL,A,(void *)("B"));
 //    pthread_create(&f3,NULL,A,(void *)("C"));
   
 //    pthread_join(prothread,NULL);
 //    pthread_join(conthread1,NULL);
 //    pthread_join(conthread2,NULL);
 //    pthread_join(conthread3,NULL);
 //    pthread_join(f1,NULL);
 //    pthread_join(f2,NULL);
 //    pthread_join(f3,NULL);
 //    sem_destroy(&mutex); 
 //    sem_destroy(&full); 
 //    sem_destroy(&empty); 
 //    sem_destroy(&mutexfile); 



	





 // 	pthread_t threads[THREAD_CNT]; 
	// unsigned long int cnt = 10000000;
	// int i= 0; 
	// for(; i<THREAD_CNT; i++) {
 // 		pthread_create(&threads[i], NULL, count, (void *)((i+1)*cnt));
 // 	}
 // 	void *v;
 // 	int k; 
 // 	for(i = 0; i<THREAD_CNT; i++) {
 // 		printf("%d exited %d\n",i,pthread_join(threads[i], &v));
 // 		k =i ;
	// }
 // 	printf("in main\n");
 // 	printSomeThreads();
 // 	printf("thread %d exited with value %ld\n",k,(unsigned long int)v);
 	
 // 	printf("end main\n");
    // cool demo 
    
	return 0;
}
