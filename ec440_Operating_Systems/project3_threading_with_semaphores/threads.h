#ifndef THREADS_H_
#define THREADS_H_
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<setjmp.h> 
#include<pthread.h>
#include<semaphore.h>

// registers 
#define JB_RBX 0 
#define JB_RBP 1
#define JB_R12 2
#define JB_R13 3
#define JB_R14 4
#define JB_R15 5
#define JB_RSP 6
#define JB_PC 7

#define QUANTA 50000//50 ms 
#define Stack_L 32767// stack size 
#define ThreadN 128// number of threads
// structure def 

//potentially just make a linked list for all semephores// didn need to  

typedef struct tcb{// used for threads type
	int threadID; // an int from 0-ThreadN with the index of the process 0 is reserved for main 
	void * stack_Space; // a pointer to the stack 
	int status;// 0= unassigned, 1 = qued, 2 = runing 3 exited  
	jmp_buf place; // the context of the thread
	int blocked;// is it blocked 
	int wantedBy; // who wants a return value from it, by default -1
	void  *value_waitedOn;// could have been just exited but store the waited for processes exit value 
	void *exitValue;// saves current process exit value 

	int sem; // has sem id that is blocking it 
}tcb;

typedef struct semf{// used for threads type
	sem_t *semi;// dont think I need
	int semid;// the current semphore id used to block processes 
	unsigned currentVal;// the current value of the semephore 
	int intialized;// a bool to see if it has been intialized 
	//int tcbswaitingforme[ThreadN];
}semf;


struct tcb TCB[ThreadN];

// given functions 
unsigned long int ptr_demangle(unsigned long int p);
unsigned long int ptr_mangle(unsigned long int p);
void *start_thunk();
void pthread_exit_wrapper();// put this as the exit function 

void pthread_exit(void *value_ptr);
// helper functions for exit
void exitAll();// should not be used with correct use of join 


pthread_t pthread_self(void); 

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg);
// helper functions for create
void intializeMain();
void intialize();

void scheduler(int signum);

// hw 3 functions
int pthread_join(pthread_t thread, void **value_ptr);
void unlock();
void lock();
// intuition for semaphore  from 
//https://www.youtube.com/watch?v=ukM_zzrIeXs&ab_channel=JacobSorber
int sem_init(sem_t *sem, int pshared, unsigned value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);


// debuging functions.
void printRegs(jmp_buf s, int meth);
void printSomeThreads();
void printSem(sem_t *sem);
long int waitFactorial(int n);
#endif