#ifndef EC440THREADS_H_
#define EC440THREADS_H_
#include <stdio.h>
struct cat{
	int age; 
	char name[10];
	bool gender; 
	char type; 
};

//int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg);
//void pthread_exit(void *value_ptr);
//pthread_t pthread_self(void);
//struct Tstate{ 
   // set of regs
   // stack pointer
   //int status;
   // should store all of these in an  Tstate array[128]
//};

//void schedule();


#endif