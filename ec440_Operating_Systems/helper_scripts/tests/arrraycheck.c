#include <stdio.h>
void testfunc(int ja){
	
	int arr[ja][2];
	int k = arr[ja-1][1];
	printf("%d",k);
}
int main(){
	int in; 
	scanf("%d",&in);
	testfunc(in);
	return 0; 
}
