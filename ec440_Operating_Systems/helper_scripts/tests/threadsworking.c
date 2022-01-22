#include"threads.h"
int CurrentThread =-1; // keeps track of the TCB index of the current thread
int threadsCreated = 1;// a bool to see if main has been initallized 

int SemNum = 1; 
int locked = 0;

// should have given all helper functions a static context but couldnt get it to work
pthread_t pthread_self(void){return (pthread_t)(CurrentThread);}// this is the one line of code I used. 

// helper functions for pthread_exit
void exitAll(){// meant to free all non finished process but abandoned after the piazza post
	int i  =1;
	for(;i<ThreadN;i++){// end current funct
			if(TCB[i].status ==1 || TCB[i].status ==2 ){
				printf("exiting %d early\n",TCB[i].threadID);
				free((TCB[i].stack_Space-(Stack_L)+8));
				TCB[i].status = 0;
			}
		} 
}

void pthread_exit(void *value_ptr){// used to exit a thread 
	lock();
	TCB[CurrentThread].status = 3;// sets threads status to exited 
	TCB[CurrentThread].exitValue = value_ptr;
	printf("\n%d just exited\n",CurrentThread);
	if(TCB[CurrentThread].threadID == 0){// checks to see if it is main. broken 
		exitAll();
	}// end on mains exit (should have it free all remaining threads) but doesn
	
	else{

		if(TCB[CurrentThread].wantedBy>-1){// problem if multilple treads joining on the same thead.  
			TCB[CurrentThread].blocked = 0;
			int joinToThread = TCB[CurrentThread].wantedBy;
			TCB[CurrentThread].wantedBy =-1;

			TCB[joinToThread].value_waitedOn = TCB[CurrentThread].exitValue;
			TCB[joinToThread].blocked = 0;
		}else{
			printf("not joined...gross\n");
		}
		free((TCB[CurrentThread].stack_Space-(Stack_L)+8));
		
	}
	//add loop to check for all exit
	unlock();
	scheduler(0);// runs scheduler 

	printf("wait what the heck nothings changed?");
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
	TCB[0].blocked = 0;
	TCB[0].wantedBy = -1;
	TCB[0].value_waitedOn = NULL;
	TCB[0].sem = 0;
	int i = 1;
	for (;i<ThreadN;i++){// intiallizes values of TCB, probly unnessiary but it was useful for debug. 
		TCB[i].threadID = -1;
		TCB[i].status = 0;
		TCB[i].sem = 0;
		TCB[i].blocked = -1;
		TCB[i].wantedBy = -1;
	}

	// setup main section 
	if(!setjmp(TCB[0].place)){// start thread process

		TCB[0].place[0].__jmpbuf[JB_RSP] = ptr_mangle((long unsigned int)&pthread_exit);// does nothing probably will comment out 
		
		CurrentThread =0;// sets up main as the first to run 
		//ualarm(QUANTA,0);// starts timer 
		longjmp(TCB[0].place,1);
	}
}
void intialize(int id,void *arg,void *(*funct) (void *)){// intializes all but main
	TCB[id].threadID = id;// sets up thread id 
	TCB[id].blocked = 0; // not waiting on another proeccess
	TCB[id].wantedBy =-1;
	TCB[id].sem = 0;
	TCB[id].value_waitedOn = NULL;

	setjmp(TCB[id].place);// set context for jump buff 

	//vvvvvvv all the bellow stuff  I got stuck on untill talking it through at OH 
	TCB[id].stack_Space = (void*)malloc(Stack_L); //creats stack      // currently at the bottom need to do stack size - 8 so its at the top 
	TCB[id].stack_Space=TCB[id].stack_Space+(Stack_L)-8;// moves stack pointer to top and then down by 8 to leave room for itself// kind  
	*(long unsigned int *)TCB[id].stack_Space= (long unsigned int)&pthread_exit_wrapper;// cast stack space into an long unsigned int @152_f1 to allow the running of exot  
	TCB[id].place[0].__jmpbuf[JB_RSP] = ptr_mangle((long unsigned int)TCB[id].stack_Space); // sets the rsp to our allocated sctac 
	//^^^^^^

	TCB[id].place[0].__jmpbuf[JB_PC] = ptr_mangle((long unsigned int) start_thunk); // starts the procram with start thunk
    TCB[id].place[0].__jmpbuf[JB_R13] = (long unsigned int) arg;// sets the args and funct to th regs specifed by the hw 
	TCB[id].place[0].__jmpbuf[JB_R12] = (long unsigned int) funct;	
	TCB[id].status = 1;
}

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg){//create new thread	
	lock();
	if(threadsCreated)intializeMain();// intialized main, used to have a print funct thats why th {}
	int i,someZeros =0;
	for(i=1;i<ThreadN;i++){// check the TCB for not assigned or exited process
		if(TCB[i].status == 0){ // look for empthy thread
			someZeros =1;
			break;  
		}
		
	}
	for(i=1;i<ThreadN && !someZeros;i++){// turns all exited process into free
		if(TCB[i].status == 3){ 
			TCB[i].status = 0;
		}
		
	}  
	for(i=1;i<ThreadN;i++){// check the TCB for not assigned or exited process
		if(TCB[i].status == 0){ // look for empthy thread
			intialize(i,arg,start_routine);// intialize it 
			*thread = i;
			printf("\nmade thread with id %d\n", TCB[i].threadID);
			break;  
		}
		
	}
	unlock();
	ualarm(QUANTA,0);
	return 0; 
}

void unlock(){
	if (locked){
	//set sigmask to unblockeding
	sigset_t mask;// taken from https://www.linuxprogrammingblog.com/code-examples/blocking-signals-with-sigprocmask
	sigemptyset (&mask);
	sigaddset (&mask, SIGALRM);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
	//pause();
	locked = 0; 
	//ualarm(QUANTA,0);
	}
	else{
		perror("NO LOCK");
	}
}
void lock(){
	if(!locked){
	//set sigmask to blockeding
	sigset_t mask;// taken from https://www.linuxprogrammingblog.com/code-examples/blocking-signals-with-sigprocmask
	sigemptyset (&mask);
	sigaddset (&mask, SIGALRM);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	locked = 1; 
	}
	else{
		perror("alreadyLocked");
	}
}

int pthread_join(pthread_t thread, void **value_ptr){// add in clause about there not being an available
	int retVal =-1; 
	int picked = (int)thread;
	if(TCB[picked].status == 0){
		perror("\nthis thread was not intialized\n");
		return retVal;
	}
	if(TCB[picked].status == 3){
		printf("\nyour playing with fire doing this did you know that? neg one but ill try and give you a val\n");
		if(value_ptr != NULL&&TCB[picked].exitValue != NULL){ *value_ptr=(TCB[picked].exitValue);
			return 0;
		}
		else printf("couldnt do it\n");
		return retVal;
	}
	lock();
	TCB[CurrentThread].blocked = 1;
	if(TCB[picked].wantedBy == -1) {
		retVal = 0;
		TCB[picked].wantedBy = pthread_self();
		printf("\n%d is now waiting\n",(unsigned int)pthread_self());
	}
	else{ 
		retVal = -3;
		perror("\nthis thread is already being joined\n");
	} 
	unlock();// check for different alarms maybe call scheduler explicitly in unlock 
	scheduler(14); 

	if(value_ptr != NULL){
		*value_ptr=(TCB[CurrentThread].value_waitedOn);
	}
	return retVal; 
}

// to get sem_t pointer to point to struct 
//sem->__align; // sem is either a pointer or a struct man align. set structure = to the smephor 
int sem_init(sem_t *sem, int pshared, unsigned value){
	lock();
	semf *d = malloc(sizeof(semf*));
	//d.semi = malloc(sizeof(semf*));
	d->semi = sem;
	d->semid = SemNum;
	SemNum++;
	//d->tcb_link = -1;
	d->currentVal = value;
	d->intialized =1;
	sem->__align = (long int)d;
	//semf * a =(semf *) sem->__align;
	unlock();
	printSem(sem);
	return 0;
}

int sem_wait(sem_t *sem){
	lock();
	semf * a =(semf *) sem->__align;
	//int currentVals = a->currentVal;// get sem value
	TCB[CurrentThread].sem = a->semid;
	unlock();
	while(1){
		lock();
		printf("\nchecking...");
		if(a->currentVal>0){
			 // might just be current tcb
			TCB[CurrentThread].sem = 0;  
			printf("success on %d from %d\n",a->semid,CurrentThread);
			a->currentVal --;
			unlock();
			break;
		}
		else{
			TCB[CurrentThread].sem = a->semid;
			printf("fail on %d from %d\n",a->semid,CurrentThread);
			unlock();
			scheduler(14); 
		}
		
	}
	ualarm(QUANTA,0);
	//sleep(1);
	return 1;
}

int sem_post(sem_t *sem){
	lock();
	semf * a =(semf *) sem->__align;
	int i = 0;
	if(a->currentVal <1){
		printf("\nunblocking %d\n",a->semid);
		for(i =0 ;i<ThreadN;i++){// check for qued process from beging, used to go till newstart-1 but I took that out durring a debug
			if(TCB[i].sem == a->semid){//&&TCB[i].blocked == 0;
				printf("%d\n",i);
				TCB[i].sem = 0; 
			}
		} 
		printf("done\n");
	}
	a->currentVal ++;
	unlock();
	scheduler(14); 
	return 1;
}

int sem_destroy(sem_t *sem){
	lock();
	semf * a =(semf *) sem->__align;
	a->semid = -1;
	a->currentVal = -1;
	//a->tcb_link = -1;
	a->intialized = 0;
	free(a);
	unlock();
	return 1;
}
//int sem_init(sem_t *sem, int pshared, unsigned value){return -1;}
//int sem_wait(sem_t *sem){return -1;}
//int sem_post(sem_t *sem){return -1;}
//int sem_destroy(sem_t *sem){return -1;}

// add a lock and unlock in scheduler 
void scheduler(int signum){ // preserve current state and then pick new process to run 
	if(!setjmp(TCB[CurrentThread].place)){// save current threads place so that it can return this function into itself
		lock();
		int newstart =0,checkDone =0,i;// i and newstart could be the same thing but it helps me conceptualize 
		// check done is used so that the second for loop can be skipped if possible 

		if(signum == SIGALRM){//checks to see if the scheduler was called in exit or because of SIGALARM,
			TCB[CurrentThread].status = 1; }// sets the status to qued
		newstart = CurrentThread+1;// starts the round robin on the next index 

		for(i = newstart;i<ThreadN;i++){// goes through the thread list to find the next qued thread 
			
			if(TCB[i].status ==1 && TCB[i].blocked == 0 && TCB[i].sem == 0){//&&!TCB[i].blocked
				CurrentThread = i;// changes the global thread to this one 
				TCB[i].status = 2;// sets status to running
				checkDone = 1; // done to skip the next for loop could have intialized it to 1 and set it to 0 her.. opps
				break;
			}
		}
		for(i =0 ;i<ThreadN&&!checkDone;i++){// check for qued process from beging, used to go till newstart-1 but I took that out durring a debug
			
			if(TCB[i].status == 1  && TCB[i].blocked == 0 && TCB[i].sem ==0){// make a helper function to see if its ready 
				CurrentThread = i;//same 
				TCB[i].status = 2;//same
				checkDone = 1; 
				break;
			}
		} 
		if(!checkDone){
			perror("not supposed to run-inschedle line 191\n");
			printf("%d\n",signum);
			printSomeThreads();
			exit(30);
		}
		unlock();// restarts the timer
		ualarm(QUANTA,0);
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
void pthread_exit_wrapper()// put this as the exit function 
{
	unsigned long int res;
	asm("movq %%rax, %0\n":"=r"(res));
	pthread_exit((void *) res);
}

// debug helper functions
void printRegs(jmp_buf s,int meth){// used to print registers 
	if(meth ==1){
	printf("\nmangled:\nRBX: Ox%08lx\nRBP: Ox%08lx\nR12: Ox%08lx\nR13: Ox%08lx\nR14: Ox%08lx\nR15: Ox%08lx\nSP: Ox%08lx\nPC: Ox%08lx\n",
		    s[0].__jmpbuf[JB_RBX],s[0].__jmpbuf[JB_RBP],s[0].__jmpbuf[JB_R12],s[0].__jmpbuf[JB_R13],s[0].__jmpbuf[JB_R14],s[0].__jmpbuf[JB_R15],s[0].__jmpbuf[JB_RSP],s[0].__jmpbuf[JB_PC]);
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
	lock();
	int i =0;
	int numT = 28; 
	printf("ID:");
	for (;i<numT;i++){
		printf("%d ",TCB[i].threadID);
	}
	printf("\n");
	printf("ST:");
	for (i =0 ;i<numT;i++){
		printf("%d ",TCB[i].status);
	}
	printf("\n");
	printf("WT:");
	for (i =0 ;i<numT;i++){
		printf("%d ",TCB[i].blocked);
	}
	printf("\n");
	printf("TG:");
	for (i =0 ;i<numT;i++){
		printf("%d ",(unsigned int)TCB[i].wantedBy);
	}
	printf("\n");
	printf("SEM:");
	for (i =0 ;i<numT;i++){
		printf("%d ",(unsigned int)TCB[i].sem);
	}
	printf("\n");
	
	unlock();
	ualarm(QUANTA,0);
}
void printSem(sem_t *sem){
	semf * a =(semf *) sem->__align;
	printf("sem id:%d\nsem val:%u\nintialized:%d\n",a->semid,a->currentVal,a->intialized);
}

// what do I need to test 
// - see if I can access a sem_T* as my sem struct if not need to figure out a good schema to do this 
// - other things 