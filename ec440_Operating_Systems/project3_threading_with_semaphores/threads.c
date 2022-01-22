#include"threads.h"
int CurrentThread =-1; // keeps track of the TCB index of the current thread
int threadsCreated = 1;// a bool to see if main has been initallized 

int SemNum = 1; // the id of a sem;
int locked = 0;// a bool to see if a lock intrustion has been issued 

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
}// should never be used 

void pthread_exit(void *value_ptr){// used to exit a thread 
	lock();
	TCB[CurrentThread].status = 3;// sets threads status to exited 
	TCB[CurrentThread].exitValue = value_ptr;// saves exit value on tcb 
	///printf("\n%d just exited\n",CurrentThread);
	if(TCB[CurrentThread].wantedBy>-1){//checks to see that this thread was wanted 
		TCB[CurrentThread].blocked = 0;//unjoin blocks thread, probably unessisary
		int joinToThread = TCB[CurrentThread].wantedBy;//saves wanted value 
		TCB[CurrentThread].wantedBy =-1;//resets it to 0 

		TCB[joinToThread].value_waitedOn = TCB[CurrentThread].exitValue;//saves exit value to waiting value
		TCB[joinToThread].blocked = 0;// unblocks thread
	}
	//else printf("not joined...gross\n");
	free((TCB[CurrentThread].stack_Space-(Stack_L)+8));// frees memory
		
	unlock();
	scheduler(0);// runs scheduler 
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
	// could all be in the for loop execpt for status but this helps 
	TCB[0].status = 2;//sets main to running 
	TCB[0].threadID =0;// gives main the id 0 
	TCB[0].blocked = 0;// sets main as unblocked 
	TCB[0].wantedBy = -1;// not joined on yet 
	TCB[0].value_waitedOn = NULL;// intialized requested pointed to null
	TCB[0].sem = 0;// sets the semephore flag to not sem blocking 
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
		longjmp(TCB[0].place,1);
	}
}
void intialize(int id,void *arg,void *(*funct) (void *)){// intializes all but main
	TCB[id].threadID = id;// sets up thread id 
	TCB[id].blocked = 0; // not waiting on another proeccess
	TCB[id].wantedBy =-1;
	TCB[id].sem = 0;// not sem blocked 
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
	lock();// camben advised that I lock anywhere global variables were changed 
	if(threadsCreated)intializeMain();// intialized main
	int i,someZeros =0;

	///vvv done to allow for functions that exit before joining to try to recover exit value
	for(i=1;i<ThreadN;i++){// check the TCB for not assigned or exited process
		if(TCB[i].status == 0){ // look for empthy thread
			someZeros =1;
			break;  
		}
		if(TCB[i].status == 0){
			someZeros = 1;
			break;
		}
	}
	for(i=1;i<ThreadN && !someZeros;i++){// turns all exited process into free
		if(TCB[i].status == 3){ 
			TCB[i].status = 0;
		}
		
	}
	///^^^^^  
	for(i=1;i<ThreadN;i++){// check the TCB for not assigned or exited process
		if(TCB[i].status == 0){ // look for empthy thread
			intialize(i,arg,start_routine);// intialize it 
			*thread = i;// links thread to the thread created 
			///printf("\nmade thread with id %d\n", TCB[i].threadID);
			break;  
		}
		
	}
	unlock();
	ualarm(QUANTA,0);// starts the alarm for scheduler 
	return 0; 
}
//set sigmask to unblocking
void unlock(){
	if (locked){// checks to see if there is anything to unlock
		sigset_t mask;// taken from https://www.linuxprogrammingblog.com/code-examples/blocking-signals-with-sigprocmask
		sigemptyset (&mask);
		sigaddset (&mask, SIGALRM);
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		locked = 0; 
	}
	else{
		perror("NO LOCK ");
	}
}
//set sigmask to blocking
void lock(){
	if(!locked){
	sigset_t mask;// taken from https://www.linuxprogrammingblog.com/code-examples/blocking-signals-with-sigprocmask
	sigemptyset (&mask);
	sigaddset (&mask, SIGALRM);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	locked = 1; 
	}
	else{
		perror("DOUBLE LOCK ");
	}
}
// blocks proccess that are running 
int pthread_join(pthread_t thread, void **value_ptr){
	int retVal =-1; // intializes a return value to a recognizbale number
	int picked = (int)thread;// gets index of the thread.

	// allows people to try and join to closed threads vvvvv
	if(TCB[picked].status == 0){// checks to see if thread is actually initialized.
		perror("\nthis thread was not intialized\n");
		return retVal;
	}
	if(TCB[picked].status == 3){// checks to see if it is exited and if the exit value was preserved 
		// not supposed to reach
		//printf("\nyour playing with fire doing this did you know that? neg one but ill try and give you a val\n");
		if(value_ptr != NULL&&TCB[picked].exitValue != NULL){ *value_ptr=(TCB[picked].exitValue);
			return 0;
		}
		//else printf("couldnt do it\n");
		return retVal;
	}
	//^^^^^^^

	lock();
	TCB[CurrentThread].blocked = 1;// sets value to blocked 
	if(TCB[picked].wantedBy == -1) {// checks to see if target thread was not joined on 
		retVal = 0;// sets a successful return value 
		TCB[picked].wantedBy = pthread_self();//set target thread of thread to the current process 
		///printf("\n%d is now waiting\n",(unsigned int)pthread_self());
	}
	else{ 
		retVal = -3;// diffferent error return value
		perror("\nthis thread is already being joined\n");
	} 
	unlock();

	scheduler(14); // calls the scheduler with the sigalarm code. 

	if(value_ptr != NULL){// when it resumes its assumed that value_ptr may have been changed
		*value_ptr=(TCB[CurrentThread].value_waitedOn);
	}
	return retVal; 
}

// initalize the sem struck and give it nessisary values 

int sem_init(sem_t *sem, int pshared, unsigned value){
	lock();

	semf *d = malloc(sizeof(semf*));// done to make d referanceable outside of this function 
	d->semi = sem;// sets the semi field to itself.... never used but it was on the hw hints
	d->semid = SemNum;// sets the sem id to the current sem number, can never use old sem numbers 
	SemNum++;// incrementsthe sem number 

	d->currentVal = value;// passes in the value 
	d->intialized =1;// intialized state set 
	sem->__align = (long int)d;// puts the pointer d into the sem->__align field. from piazza and the semephore.h description

	unlock();
	///printSem(sem);
	return 0;
}
// down fucntion for sem
int sem_wait(sem_t *sem){
	lock();
	semf * a =(semf *) sem->__align; // creates a helper variable for sem so sem is preserved
	if (a->intialized == 0) exit(42);// makes sure arg was intialized 

	TCB[CurrentThread].sem = a->semid;// blocks the current thread with code semid 
	unlock();
	// done in while to make sure they wake up 
	// could have used the if statement as the while conditional but wanted  lock and unlock around variable assignment
	while(1){
		lock();
		///printf("\nchecking...");
		if(a->currentVal>0){
			//if it can be decremented then set the sem feild to non blocking 
			TCB[CurrentThread].sem = 0;  
			///printf("success on %d from %d\n",a->semid,CurrentThread);
			a->currentVal --;// decrement sem value 
			unlock();
			break;// leave the loop 
		}
		else{
			// at this point the sem id is 0 because of a post call or an ititial fail of the currval condion
			// may be unnessisary but helpful conceptually
			TCB[CurrentThread].sem = a->semid;// resets semid to 0; 
			///printf("fail on %d from %d\n",a->semid,CurrentThread);
			unlock();
			scheduler(14); // explicitly calls scheduler with sigalarm code 
		}
		
	}
	ualarm(QUANTA,0);// resets the timer to compensate for lock unlock
	return 1;
}
// the same as up in semiphore 
int sem_post(sem_t *sem){ 
	lock();
	semf * a =(semf *) sem->__align;
	if (a->intialized == 0) exit(42); 
	if(a->currentVal <1){
		///printf("\nunblocking %d\n",a->semid);
		int i = 0; 
		for(i =0 ;i<ThreadN;i++){// check for blocked process from beging and unblocks them 
			///printf("%d\n",i);
			TCB[i].sem = 0; 
		} 
		///printf("done\n");
	}
	a->currentVal ++;// here the sem is added to 
	unlock();
	scheduler(14); // explicitly calls scheduler to allow blocked process a go at the semaphore 
	return 0;
}
// cleans up semaphore 
int sem_destroy(sem_t *sem){
	lock();
	// could have added a loop in here that unblocks all the treads blocked on it which would have 
	// stoped infinate loop but behavior is undefined and I passed all the tests . 

	semf * a =(semf *) sem->__align;
	if (a->intialized == 0) exit(42);
	a->semid = -1;//may be unnessisary
	a->currentVal = -1;//may be unnessisary
	a->intialized = 0;//important allows porcess to see that this is not a semaphore 
	free(a);// frees memory on a which hopefully makes the above steps pointless
	unlock();
	return 0;
}


// helper function to see if it cann be scheduled 
int CanBeScheduled(int index){
	int ready = TCB[index].status ==1; 
	int notJoinBlocked = TCB[index].blocked == 0; 
	int notSemBlocked =TCB[index].sem == 0;
	return ready && notSemBlocked && notJoinBlocked;
}

void scheduler(int signum){ // preserve current state and then pick new process to run 
	if(!setjmp(TCB[CurrentThread].place)){// save current threads place so that it can return this function into itself
		lock();
		int newstart =0,checkDone =0,i;// i and newstart could be the same thing but it helps me conceptualize 
		// check done is used so that the second for loop can be skipped if possible 

		if(signum == SIGALRM){//checks to see if the scheduler was called in exit or because of SIGALARM,
			TCB[CurrentThread].status = 1; 
		}// sets the status to qued
		
		newstart = CurrentThread+1;// starts the round robin on the next index 
		for(i = newstart;i<ThreadN;i++){// goes through the thread list to find the next qued thread 
			if(CanBeScheduled(i)){
				CurrentThread = i;// changes the global thread to this one 
				TCB[i].status = 2;// sets status to running
				checkDone = 1; // done to skip the next for loop could have intialized it to 1 and set it to 0 her.. opps
				break;
			}
		}
		for(i =0 ;i<ThreadN&&!checkDone;i++){// check for qued process from beging, used to go till newstart-1 but I took that out durring a debug
			if(CanBeScheduled(i)){// make a helper function to see if its ready 
				CurrentThread = i;//same 
				TCB[i].status = 2;//same
				checkDone = 1; 
				break;
			}
		} 
		if(!checkDone){
			perror("not supposed to run-inschedle line 334\n");
			printf("%d\n",signum);
			printSomeThreads();
			exit(30);
		}
		unlock();
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
void printSem(sem_t *sem){// prints a semaphors value 
	semf * a =(semf *) sem->__align;
	printf("sem id:%d\nsem val:%u\nintialized:%d\n",a->semid,a->currentVal,a->intialized);
}
