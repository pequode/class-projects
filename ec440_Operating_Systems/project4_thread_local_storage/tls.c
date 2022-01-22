#include"tls.h"// include .h file 

int initialized = 0; // flag to see if it is intialize 
int page_size = page_sizeDef;// the page size thats assumed on bandit 
int prt= 1; // boolean to decide if statements should print 
int tls_create(unsigned int size){
	if(prt)printf("\tin create\n");//
	//VVV check for error conditions 
	pthread_t T_id =pthread_self();// gets this threads T_id so it can be reffenced 
	int tlsId = findTLSIndexself();// checks to see if its in the array of tls's  
	if(size<=0) // bad size 
	{
		if(prt)printf("\tsorry must initialize with a none 0 size- create\n");
		return -1; 
	}
	if(tlsId != -1 ){ // not an empty thead
			if(prt)printf("\tthis thread already has a tls - create\n");
			return -1;
	}
	int i; 
	for(i=0;i<MaxThread;i++){// check the TLS for  another thread. 
		if(T_id ==TLSIndex[i].tid && TLSIndex[i].inited == 1 ){
			if(prt)printf("\tthread already has an index and was initialized - create\n");
			return -1;
		}
	}
	//^^^^^ check for error conditions 
	// finds a non initialized tls index
	for(i=0;i<MaxThread;i++){
		if(TLSIndex[i].inited == 0){ 
			tlsId =i;
			break;  
		}
	}
	if(tlsId == -1) { // makes sure there was a spot to intialize to 
		if(prt)printf("\tsorry no more tls spots available- create\n");
		return -1;
	}
	if (!initialized) tls_init(); // from disc slide // runs if never run before
	int pageN = (size/page_size)+1;// get number of pages
	Pages ** pg=(Pages**)calloc(pageN, sizeof(Pages**)); // allocate memory for pages
	if(prt)printf("\tsetting id:%d tid:%d\n",tlsId,(int)T_id);
	setTls(tlsId,T_id,size,pageN,pg,0);// sets up tls execpt for initialized. 
	// from slides vvvv
	for(i=0 ;i<pageN;i++){// populate the pages with empty memory 
		pg[i] = (Pages*)calloc(1, sizeof(Pages*));// create space for each page 
		pg[i]->address = mmap(0,page_size, 0, MAP_ANON | MAP_PRIVATE,0, 0);//creates a protected memory region  
		if(pg[i]->address  == (void *)-1) {// checks for a mmap failure
			if(prt)printf("\tfailed mmap\n");
			return -1;
		} 
		pg[i]->ref_count = 1;// sets the current threads referance to this thread. 
	}
	// from slides ^^^^
	TLSIndex[tlsId].inited = 1;// marks the current thread as initialized
	if(prt)printf("\tcreated %d\n",tlsId);
	return 0; 
}
int tls_clone(pthread_t tid){// create a clone of the tartget tls 
	pthread_t T_id = pthread_self();// gets this thread T_id
	int tlsId = findTLSIndexself();// checks to see if the current thread has an assosiated tls
	int tlsTarget = findTLSIndex(tid);// gets the tls index of the target thread
	int targtsiz = (int)TLSIndex[tlsTarget].size;// checks the target size to make sure its more than 0 
	//VVV check for error conditions 
	if(tlsId != -1 ){ // look for empthy thread
			if(prt)printf("\tsorry this thread already has a tls because its mapped- clone\n");
			return -1;
	}
	if(tlsTarget == -1 ){ // look for empthy target thread
			if(prt)printf("\tsorry the target doesnt have a tls because not mapped- clone\n");
			return -1;
	}
	if(targtsiz <=0)// check target thread size
	{
		if(prt)printf("\tsorry target thread has no tls because of size-clone\n");
		return -1; 
	}
	int i;
	for(i=0;i<MaxThread;i++){// check the TCB for not assigned or exited process
		if(TLSIndex[i].inited == 0){ // look for empthy thread
			tlsId =i;
			if(prt)printf("\tmy index is %d\n",tlsId);
			break;  
		}
	}
	if(i == MaxThread) {// check to see if all tls spaces used 
		if(prt)printf("\tsorry no more tls spots available- clone\n");
		return -1;
	}
	//^^^check for error conditions 
	unsigned int Targetsize = TLSIndex[tlsTarget].size; // creats this var for convience
	unsigned int pageNum = TLSIndex[tlsTarget].page_num;//creats this var for convience
	Pages ** pg=(Pages**)calloc(pageNum, sizeof(Pages**));// manipulation variable 
	setTls(tlsId,T_id, Targetsize,pageNum,pg,0);// sets the tls execpt for a successful init code.
	// from lecture VVVV
	for(i=0 ;i<pageNum;i++){// iterate through the pages 
		Pages *p;// create a point place holder 
		p = TLSIndex[tlsTarget].pages[i];//gives p the adress of the target tls.pages
		if(p->address  == NULL){// checks to make sure that the page adress is non null should be not nessisary becasue of 
			if(prt)printf("\tsorry page address null\n");
		 	return -1; 
		}
		p->ref_count++;// increments the page counter because the clone is also using this elemeng
		TLSIndex[tlsId].pages[i] = p;// assigns the new page to the current target 
	}
	// from lecture ^^^
	TLSIndex[tlsId].inited =1;// fininish the initialization
	if(prt)printf("\t%d cloned %d \n",tlsId,tlsTarget);
	return 0; 
}
int tls_destroy(){//frees all vars 
	int tlsId = findTLSIndexself();// gets the current thread tls id 
	if(prt)printf("\t%d is the tlsid\n",tlsId);
	// vvv check for failure condions 
	int k = (int)TLSIndex[tlsId].size;
	if(!(k >0)|| tlsId ==-1) // make sure it has size and was ininitalized
	{
		if(prt)printf("\tsorry this thread has no tls- destroy\n");
		return -1; 
	}
	//^^ check for failure condions 
	Pages **p = TLSIndex[tlsId].pages;// creates a pointer for convience
	int i;  
	for(i =0;i<TLSIndex[tlsId].page_num;i++){// goes through all pages and frees the ones that are only refferanced by this page
		//vvv from lecture
		if(prt)printf("\t %d and ref count %d\n",i,p[i]->ref_count);
		
		p[i]->ref_count --; // decraments the page refrance counter
		if (p[i]->ref_count<1){// if its the last refrance free the page
			int err = munmap(p[i]->address, page_size);
			if(err == -1) return -1;
			if(prt)printf("\n\tfreeing page %d from %d\n",i,tlsId);
			
			free(TLSIndex[tlsId].pages[i]);
		}
	}
	free(TLSIndex[tlsId].pages);// frees the pages section 
	//^^^from lecture
	setTls(tlsId,-1,0,0,TLSIndex[tlsId].pages,0);// sets the page to unitialized 
	if(prt)printf("\t%s %d\n","done destroy",tlsId);
	return 0; 
}

int tls_read(unsigned int offset, unsigned int length, char *buffer){
	
	int tlsId = findTLSIndexself();// finds the 
	int TslSize = (int)TLSIndex[tlsId].size;// gets the size of the current tls
	//vvv checks for the error conditions 
	if(!(TslSize >0) || tlsId == -1)
	{
		if(prt)printf("\tsorry this thread(%d) has no tls-read\n",tlsId);
		return -1; 
	}
	if(offset+length>TslSize){
		if(prt)printf("\tsorry request is out of bounds-read\n");
		return -1; 
	} 
	//^^^ checks for the error conditions 
	// Lecture code
	unprotectAllPages();
	int cnt,idx; 
	char *src; 
	for (cnt = 0, idx = offset; idx < (offset +length); ++cnt, ++idx) {
		Pages *p;
		unsigned int pn, poff;
		pn = idx / page_size;
		poff = idx % page_size;
		p = TLSIndex[tlsId].pages[pn];
		src = ((char *) p->address) + poff;
		buffer[cnt] = *src;
 	}
	protectAllPages();
	if(prt)printf("\t%s %d\n","done on read",tlsId);
	return 0; 
}
int tls_write(unsigned int offset, unsigned int length, char *buffer){// used to write to the memory location
	
	int tlsId = findTLSIndexself();
	int TslSize = (int)TLSIndex[tlsId].size;
	//vvv checks for the error conditions 
	if(!(TslSize >0) || tlsId == -1)
	{
		if(prt)printf("\tsorry this thread(%d) has no tls-write\n",tlsId);
		return -1; 
	}
	if(offset+length>TslSize){
		if(prt)printf("\tsorry request is out of bounds-write\n");
		return -1; 
	} 
	//^^^ checks for the error conditions 
	int cnt,idx; 
	char * dst; 
	for (cnt = 0, idx = offset; idx < (offset + length); ++cnt, ++idx) {
		Pages *old, *copy;
		unsigned int pn, poff;
		pn = idx / page_size;
		poff = idx % page_size;
		old = TLSIndex[tlsId].pages[pn];
		tls_unprotect(old);
		if (old->ref_count > 1) {
			
			copy = (Pages *) calloc(1, sizeof(Pages));
			//memcpy(copy,old, sizeof(Pages));
			copy->address = mmap(0,page_size, PROT_WRITE,MAP_ANON | MAP_PRIVATE, 0, 0);
			tls_unprotect(copy);
			
 			copy->ref_count++;
 			TLSIndex[tlsId].pages[pn] = copy;
 			old->ref_count--;
 			
			memcpy(copy->address ,old->address , page_size);// page_size instead of sizeof()
 			tls_protect(old);
 			old = copy;
		}
		
		dst = ((char *) old->address) + poff;
		*dst = buffer[cnt];
		tls_protect(old);
	}

	return 0; 
}



// helper 
void tls_init(){
	page_size = getpagesize();// checks to make sure that the page size is 4096
	if (page_size != page_sizeDef) printf("\tturns out the page size was %d instead of %d-tls_init\n",page_size,(int)page_sizeDef);
	//sets up the sigfault handler 
	struct sigaction sigact;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO; /* use extended signal handling */
	sigact.sa_sigaction = tls_handle_page_fault;
	sigaction(SIGBUS, &sigact, NULL);
	sigaction(SIGSEGV, &sigact, NULL);

	// checks flag for weather or not it is intialized
	initialized = 1;
	int i; 
	for(i=0;i<MaxThread;i++){// intiallized all of the tls's
		setTls(i,-1,-1,-1,NULL,0);
	}	
}
// not used used in an older implementation 
void unprotectAllPages(){
	int tlsId = findTLSIndexself();
	if(tlsId ==-1){
		if(prt)printf("\tERROR : no assosiated tls-protectallpages\n");
		return ;
	}
	int i;
	for(i=0; i< TLSIndex[tlsId].page_num;i++){
		tls_unprotect(TLSIndex[tlsId].pages[i]);
	}
}
// not used used in an older implementation 
void protectAllPages(){
	int tlsId = findTLSIndexself();
	if(tlsId ==-1){
		if(prt)printf("\tERROR :no assosiated tls-protectallpages\n");
		return;
	}
	int i;
	for(i=0; i< TLSIndex[tlsId].page_num;i++){
		tls_protect(TLSIndex[tlsId].pages[i]);
	}
}
// from class wrapper for mprotect to allow protecting stuff
void tls_protect(Pages *p)
{
	if (mprotect((void *) p->address, page_size, 0)) {
		if(prt)printf( "\ttls_protect: could not protect page- protect\n");
		exit(1);
	}
}
// from class wrapper for mprotect to allow unprotecting stuff
void tls_unprotect(Pages *p)
{
	if (mprotect((void *) p->address, page_size,PROT_READ | PROT_WRITE)) 
	{
		if(prt)printf("\ttls_unprotect: could not unprotect page - unprotect\n");
		exit(1);
	}
}
void tls_handle_page_fault(int sig, siginfo_t *si, void *context)// method for sig handling 
{
	//from lecture vvv
 	unsigned long int p_fault =((unsigned  long int)si->si_addr) & ~(page_size - 1);// holds the specific virtual adress of the page 
 	int tlsId = findTLSIndexself();

 	if(prt)printf("\tGot a fault it was tls id %d\n",tlsId);
 	int i;
 	for(i = 0; i<MaxThread;i++){// itterates through the available tls's and checks for the current segfault adress
 
		 	int pnum = TLSIndex[i].page_num;
		 	int k;
		 	Pages ** p = TLSIndex[i].pages;
		 	for(k =0;k < pnum; k++){
			 	if ((unsigned long int)p[k]->address == p_fault) {
			 		if(prt)printf("Not Allowed Se ya\n");
			 		pthread_exit(NULL);
			 		return;
				}
			}
	}
	if(prt)printf("Regular SegFault\n");
	//resends segFault to program 
	signal(SIGSEGV, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	raise(sig);	
	//from lecture ^^^
}
void printTLS(int k){
	int i =0;
	int TestSize = k; 
	printf("TLS table:\nT_id:\n");
	for(i=0;i<TestSize;i++){
		printf("%d ", (int)TLSIndex[i].tid);
	}
	printf("\nsize:\n");
	for(i=0;i<TestSize;i++){
		printf("%d ", (int)TLSIndex[i].size);
	}
	printf("\nN pages:\n");
	for(i=0;i<TestSize;i++){
		printf("%d ", (int)TLSIndex[i].page_num);
	}
	printf("\ninited:\n");
	for(i=0;i<TestSize;i++){
		printf("%d ", (int)TLSIndex[i].inited);
	}
	printf("\n");
	printf("page refs:\n");
	for(i=0;i<TestSize;i++){
		if(TLSIndex[i].inited){
			//int j =0;
			//for(j =0;j<TLSIndex[i].page_num;j++){
				//if(TLSIndex[i].pages[j] == NULL)break;
				//printf("%d|",TLSIndex[i].pages[j]->ref_count);
			//}
			printf(" ");
		}
		else{
			printf("X ");
		}
	}
	printf("\n");// a method for displaying the current state of threads
}
int findTLSIndex(pthread_t i){// itterates through all the tls array to see if there are any matches in the T_ids
	int k; 
	for(k=0;k<MaxThread;k++){
		if((long)TLSIndex[k].tid == (long)i){
			return k; 
		}
	}
	return -1;
}//return -1 for not found 
int findTLSIndexself(){
	//wrapper for findTLSIndex with current thread as the input
	int k = findTLSIndex(pthread_self()); 
	return k;
}//return -1 for not found 
void setTls(int tlsId,pthread_t tid, unsigned int size,unsigned int page_num,Pages **pages,int inited){
	// pretty simply
	TLSIndex[tlsId].tid = tid;
	TLSIndex[tlsId].size= size;
	TLSIndex[tlsId].page_num = page_num;
	TLSIndex[tlsId].pages =pages;
	TLSIndex[tlsId].inited =inited;// sets a tls referance, easier with struct formating 
}
