#ifndef TLS_H_
#define TLS_H_

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include <sys/mman.h>
#include <semaphore.h>
#include<string.h>
//#include"threads.h"
#define MaxThread 128
#define page_sizeDef 4096
typedef struct page {
	 void * address; /* start address of page */
	 int ref_count; /* counter for shared pages */
}Pages;
typedef struct thread_local_storage
{
	 pthread_t tid;
	 unsigned int size; /* size in bytes */
	 unsigned int page_num; /* number of pages */
	 Pages **pages; /* array of pointers to pages */
	 int inited; 
} TLS;


TLS TLSIndex[MaxThread];
// assignment 
int tls_create(unsigned int size);
int tls_write(unsigned int offset, unsigned int length, char *buffer);
int tls_read(unsigned int offset, unsigned int length, char *buffer);
int tls_destroy();
int tls_clone(pthread_t tid);
// helper 
void tls_init();
void tls_protect(Pages *p);
void tls_unprotect(Pages *p);
void unprotectAllPages();
void protectAllPages();
void tls_handle_page_fault(int sig, siginfo_t *si, void *context);
void printTLS(int k);
void setTls(int tlsId,pthread_t tid, unsigned int size,unsigned int page_num,Pages **pages,int inited);
int findTLSIndexself();
int findTLSIndex(pthread_t i);
void setOutput(FILE * k);
#endif


// plan for development 
// come up with a main 
// try to use my lib 
// worst case use phtread
// do create first and then test the seg fault stuff 
