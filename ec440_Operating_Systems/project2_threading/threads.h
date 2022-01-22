#ifndef THREADS_H_
#define THREADS_H_
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<setjmp.h> 
#include<pthread.h>

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
#define ThreadN 129// number of threads
// structure def 

typedef struct threads{// used for threads type
	int threadID; // an int from 0-ThreadN with the index of the process 0 is reserved for main 
	void * stack_Space; // a pointer to the stack 
	int status;// 0= unassigned, 1 = qued, 2 = runing 3 exited  
	jmp_buf place; // the context of the thread
	
}Threads;

struct threads TCB[ThreadN];

// given functions 
unsigned long int ptr_demangle(unsigned long int p);
unsigned long int ptr_mangle(unsigned long int p);
void *start_thunk();



void pthread_exit(void *value_ptr);
// helper functions for exit
void exitAll();

pthread_t pthread_self(void); 

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg);
// helper functions for create
void intializeMain();
void intialize();

void scheduler();


// debuging functions.
void printRegs(jmp_buf s, int meth);
void printSomeThreads();

// testing functions
typedef struct cat{
	int age; 
	char name[10];
	int place; 
	char type; 
}Cat;
void changeage(int k, struct cat *alnold);
void printcat(struct cat l);
long int waitFactorial(int n);
#endif