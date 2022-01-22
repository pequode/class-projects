#include"threads.h"
#include<pthread.h>
int CurrentThread =-1; // keeps track of the TCB index of the current thread
int threadsCreated = 1;// a bool to see if main has been initallized 
// should have given all helper functions a static context but couldnt get it to work
pthread_t pthread_self(void){return (pthread_t)(CurrentThread);}// this is the one line of code I used. 

// helper functions for pthread_exit
void exitAll(){// meant to free all non finished process but abandoned after the piazza post
	int i  =1;
	for(;i<ThreadN;i++){// end current funct
			if(TCB[i].status !=0){
				//printf("exiting %d\n",TCB[CurrentThread].threadID);
				free((TCB[CurrentThread].stack_Space-(Stack_L)+8));
				TCB[i].status = 0;
			}
		} 
}

void pthread_exit(void *value_ptr){// used to exit a thread 
	TCB[CurrentThread].status = 3;// sets threads status to exited 
	
	if(TCB[CurrentThread].threadID == 0){// checks to see if it is main. broken 
		exitAll();
		exit(0);
	}// end on mains exit (should have it free all remaining threads) but doesn
	
	else{
		free((TCB[CurrentThread].stack_Space-(Stack_L)+8));// frees the alocated mem... I think, it works with and without this line
	}

	scheduler();// runs scheduler 
	exit(40);// not supposed to return.
}

// helper functions for pthead_creat 

void intializeMain(){ // fills in arrays with values 
	//setup general section
	threadsCreated =0;//0 is the reserved index for main 

	//vvvv// inspired by  https://pubs.opengroup.org/onlinepubs/009695399/functions/sigaction.html
	struct sigaction clock;
	clock.sa_handler = scheduler;
	clock.sa_flags = SA_NODEFER;
	sigaction(SIGALRM, &clock, NULL);
	//^^^^

	TCB[0].status = 2;//sets main to running 
	TCB[0].threadID =0;// gives main the id 0 
	int i = 1;
	for (;i<ThreadN;i++){// intiallizes values of TCB, probly unnessiary but it was useful for debug. 
		TCB[i].threadID = -1;
		TCB[i].status = 0;
	}

	// setup main section 
	if(!setjmp(TCB[0].place)){// start thread process
			TCB[0].place[0].__jmpbuf[JB_RSP] = ptr_mangle((long unsigned int)&pthread_exit);// does nothing probably will comment out 
			CurrentThread =0;// sets up main as the first to run 
			ualarm(QUANTA,0);// starts timer 
			longjmp(TCB[0].place,1);
	}
}
void intialize(int id,void *arg,void *(*funct) (void *)){// intializes all but main
	TCB[id].threadID = id;// sets up thread id 
	setjmp(TCB[id].place);// set context for jump buff 

	//vvvvvvv all the bellow stuff  I got stuck on untill talking it through at OH 
	TCB[id].stack_Space = (void*)malloc(Stack_L); //creats stack      // currently at the bottom need to do stack size - 8 so its at the top 
	TCB[id].stack_Space=TCB[id].stack_Space+(Stack_L)-8;// moves stack pointer to top and then down by 8 to leave room for itself// kind  

	*(long unsigned int *)TCB[id].stack_Space= (long unsigned int)&pthread_exit;// cast stack space into an long unsigned int @152_f1 to allow the running of exot  
	TCB[id].place[0].__jmpbuf[JB_RSP] = ptr_mangle((long unsigned int)TCB[id].stack_Space); // sets the rsp to our allocated sctac 
	//^^^^^^

	TCB[id].place[0].__jmpbuf[JB_PC] = ptr_mangle((long unsigned int) start_thunk); // starts the procram with start thunk
    TCB[id].place[0].__jmpbuf[JB_R13] = (long unsigned int) arg;// sets the args and funct to th regs specifed by the hw 
	TCB[id].place[0].__jmpbuf[JB_R12] = (long unsigned int) funct;	
	TCB[id].status = 1;
}
int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg){//create new thread
	
	if(threadsCreated){intializeMain();}// intialized main, used to have a print funct thats why th {}
	int i; 
	for(i=1;i<ThreadN;i++){// check the TCB for not assigned or exited process
		if(TCB[i].status == 0||TCB[i].status == 3){ // look for empthy thread
			intialize(i,arg,start_routine);// intialize it 
			//printf("made thread with id %d\n", TCB[i].threadID);
			break;  
		}
		
	}
	return 0; 
}


void scheduler(){ // preserve current state and then pick new process to run 
	if(!setjmp(TCB[CurrentThread].place)){// save current threads place so that it can return this function into itself
		
		int newstart =0,checkDone =0,i;// i and newstart could be the same thing but it helps me conceptualize 
		// check done is used so that the second for loop can be skipped if possible 

		if(TCB[CurrentThread].status!=3){//checks to see if the scheduler was called in exit or because of SIGALARM,
			// a better way to do this would have been to add the arg into scheduler but this was done for testing and I forgot about it 
			newstart = CurrentThread+1;// starts the round robin on the next index 
			TCB[CurrentThread].status = 1;// sets the status to qued 
		}
		else{
			newstart = CurrentThread+1;// doesnt reque the thread could have done this one if statement.... opps
		}

		for(i = newstart;i<ThreadN;i++){// goes through the thread list to find the next qued thread 
			if(TCB[i].status ==1){
				CurrentThread = i;// changes the global thread to this one 
				TCB[i].status = 2;// sets status to running
				checkDone = 1; // done to skip the next for loop could have intialized it to 1 and set it to 0 her.. opps
				break;
			}
		}
		for(i =0 ;i<ThreadN&&!checkDone;i++){// check for qued process from beging, used to go till newstart-1 but I took that out durring a debug
			if(TCB[i].status ==1){
				CurrentThread = i;//same 
				TCB[i].status = 2;//same
				break;
			}
		} 
		ualarm(QUANTA,0);// restarts the timer
		longjmp(TCB[CurrentThread].place,1); // goes to the previous setjump, usually at the top of this funct but with the right context
    }//returns into the function running
}

// here are the given functions because I couldnt figure out how to link the .h for ec440
unsigned long int ptr_demangle(unsigned long int p){
    unsigned long int ret;

    asm("movq %1, %%rax;\n"
        "rorq $0x11, %%rax;"
        "xorq %%fs:0x30, %%rax;"
        "movq %%rax, %0;"
    : "=r"(ret)
    : "r"(p)
    : "%rax"
    );
    return ret;}
unsigned long int ptr_mangle(unsigned long int p){
    unsigned long int ret;

    asm("movq %1, %%rax;\n"
        "xorq %%fs:0x30, %%rax;"
        "rolq $0x11, %%rax;"
        "movq %%rax, %0;"
    : "=r"(ret)
    : "r"(p)
    : "%rax"
    );
    return ret;}
void *start_thunk() {
  asm("popq %%rbp;\n"           //clean up the function prolog
      "movq %%r13, %%rdi;\n"    //put arg in $rdi
      "pushq %%r12;\n"          //push &start_routine
      "retq;\n"                 //return to &start_routine
      :
      :
      : "%rdi"
  );
  __builtin_unreachable();
}


// debug helper functions
void printRegs(jmp_buf s,int meth){// used to print registers 
	if(meth ==1){
	printf("\nmangled:\nRBX: Ox%08lx\nRBP: Ox%08lx\nR12: Ox%08lx\nR13: Ox%08lx\nR14: Ox%08lx\nR15: Ox%08lx\nSP: Ox%08lx\nPC: Ox%08lx\n",
		    s[0].__jmpbuf[JB_RBX],s[0].__jmpbuf[JB_RBP],s[0].__jmpbuf[JB_R12],s[0].__jmpbuf[JB_R13],
			s[0].__jmpbuf[JB_R14],s[0].__jmpbuf[JB_R15],s[0].__jmpbuf[JB_RSP],s[0].__jmpbuf[JB_PC]);
	} else if(meth == 2){
		printRegs(s,1);
		printRegs(s,0);
	}
	else {
		printf("\ndemangled:\nRBX: Ox%08lx\nRBP: Ox%08lx\nR12: Ox%08lx\nR13: Ox%08lx\nR14: Ox%08lx\nR15: Ox%08lx\nSP: Ox%08lx\nPC: Ox%08lx\n",
		    ptr_demangle(s[0].__jmpbuf[JB_RBX]),ptr_demangle(s[0].__jmpbuf[JB_RBP]),ptr_demangle(s[0].__jmpbuf[JB_R12]),ptr_demangle(s[0].__jmpbuf[JB_R13]),
			ptr_demangle(s[0].__jmpbuf[JB_R14]),ptr_demangle(s[0].__jmpbuf[JB_R15]),ptr_demangle(s[0].__jmpbuf[JB_RSP]),ptr_demangle(s[0].__jmpbuf[JB_PC]));
	}
}
long int waitFactorial(int n){
	long int use = (long int)n;
	if(n>1){
		return use*waitFactorial(use-1);
	}else{
		return 1; 
	}// used to trigger timer without continuing to execute //wastes time
} 
void printSomeThreads(){ // used to  print the status of all the threads 
	int i =0; 
	for (;i<28;i++){
		printf("%d ",TCB[i].threadID);
	}
	printf("\n:");
	for (i =0 ;i<28;i++){
		printf("%d ",TCB[i].status);
	}
	printf("\n");
}

//cat functions 
void changeage(int k, Cat *alnold){	alnold->age = k;}// a function for understanding struct
void printcat(Cat l){printf("%s is %d and he is number is %d\n",l.name,l.age,l.place);}// same 
