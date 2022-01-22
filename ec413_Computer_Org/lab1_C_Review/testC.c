#include <stdio.h>
#define getName(var)  #var 
// SOLUTION FILE

char shiftby(char inchar,int i,int isRight){
  char c = inchar;
  if(isRight){
    c = c>>i;
  }else{
    c = c<<i;
  }
  return c;
}
int main()//main()
{
   int var_int;                    // 2
   char var_char;
   short var_short; 
   long var_long;
   float var_float;

  unsigned char uchar1, uchar2;   // 3
  signed char schar1, schar2;

  int x, y;                       // 4

  char i;                         // 5
  char shift_char;

  int a[10] = {0,10,20,30,40,50,60,70,80,90};    // 6

  int b[10], c[10];               // 7
  int *ip, *ip2;
  int j, k;

  char AString[] = "HAL";           // 8

  // 1 -- change "World" to your name
  printf("\n\n PART 1 ---------\n");
  //done
  printf("\n Hello George! \n");

  // 2 -- find sizes of the other C datatypes
  printf("\n\n PART 2 ----------\n");
  // done 
  printf("\n size of data type \nchar = %ld\nshort = %ld\nint = %ld\nlong = %ld\nfloat = %ld\n",sizeof(var_char),sizeof(var_short),sizeof(var_int),sizeof(var_long),sizeof(var_float));


//   // 3 -- explore signed versus unsigned datatypes and their interactions

  printf("\n\n PART 3 ----------\n");

  uchar1 = 0xFF;
  uchar2 = 0xFE;
  schar1 = 0xFF;
  schar2 = 0xFE;

  printf("\nuchar1 = %d \n", uchar1);
  printf("\nschar1 = %d \n", schar1);
//char1 and uchar1 print different values because on schar1 the first 1 in  F:1111 makes it a negitive number 
  char * name;
  name = ((int)schar1>(int) uchar1)? getName(schar1):getName(uchar1);
  printf("%s is greater val1:%d val2:%d \n",name,(int)schar1,(int)uchar1);
  name = ((int)schar2>(int) uchar2)? getName(schar2):getName(uchar2);
  printf("%s is greater val1:%d val2:%d \n",name,(int)schar2,(int)uchar2);
  printf("schar1:%d\tschar2:%d\tuchar1%d\tuchar2:%d\n",(int)schar1,(int)schar2,(int)uchar1,(int)uchar2);
  printf("1:%d\n",(int)(schar1 > uchar1));
  // the result is 0 or false meaning that u char was eveluated as 255
  printf("2:%d\n",(int)(schar1 + schar2));
  // the result was -3 as was expected
  printf("3:%d\n",(int)(uchar1 + uchar2));
  // the result was 509 as was expected
  printf("4:%d\n",(int)(schar1 + uchar1));
// the result was 254 as was expected, but also no error was thrown when mixin signed and unsighned types which is troublesome

  // 4 -- Booleans

  printf("\n\n PART 4 ----------\n");

  x = 1; y = 2;
  int tRue = 1==1;
  int fAlse =  !tRue;
  int sizeBool = (int)sizeof(1<2);// size of an int
  int differenceBit = x&y;//01  
  int differenceAnd = x&&y; 
  int sid1 = 0,sid2 = -1;
  int orBit = sid1|sid2;  
  int or = sid1||sid2; 
  printf("Val True:%d\tVal False:%d\nSize Bool:%d\nBit and:%d\tBit or:%d\nAnd:%d\tOr:%d\n",
          tRue,fAlse,
          sizeBool,
          differenceBit,orBit,
          differenceAnd,or);




  // 5 -- shifts
  printf("\n\n PART 5 ----------\n");

  shift_char = 15;
  i = 1;
  int itNum = 12;
 
  for (i=0;i<itNum;i++){
    printf("i is %d\n", i);
    printf("shift_charL << %d = %d\n", i, shift_char << i);
    printf("shift_charR >> %d = %d\n\n", i, shift_char >> i);
  }
 
//if you shift more than 4 it goes to 240 if you shift more than 7 it goes to 
//it also doubles each time it is shifted

// 6 -- pointer basics
  printf("\n\n PART 6 ----------\n");
  int printArry[7] = {-3551,-3551,-3551,-3551,-3551,-3551,-3551};

  ip = a;
  printArry[0] = a[0];
  printArry[1] = *(ip);
  printArry[2] = *(ip+1);
  printArry[3] = *ip++;
  printArry[4] = *ip;
  printArry[5] = *(ip+3);
  printArry[6] = *(ip-1);
  printf("start\n");
  for(i = 0;i<7;i++){
    printf("%d,",printArry[i]);
  }
	printf("\n");

  ip = a;
  printArry[0] = a[1];
  printArry[1] = *(ip+1);
  printArry[2] = *(ip+2);
  printArry[3] = *ip+10;
  printArry[4] = *(ip+2);
  printArry[5] = *(ip+5);
  printArry[6] = *(ip)+10;
  printf("modCont\n");
  for(i = 0;i<7;i++){
    printf("%d,",printArry[i]);
  }
  printf("\n");
  printf("size:%ld\n",sizeof(ip));
  printf("way 1 %d way 2 %x\n",ip,ip);
  // What  happens when  you print the pointer values  themselves? 
  // you get random numbers, they are easier to read in hex
  // the differeence is that ip is the first element in the array, ip +1 is the second element in the array

//   // 7 -- programming with pointers
  printf("\n\n PART 7 ----------\n");
  ip = a;
  for(i = 9,j = 0;i>-1;i--,j++){
    b[j]=a[i];
    printf("%d,",b[j]);
  }
  printf("\n");

  for(i = 9,j = 0;i>-1;i--,j++){
    c[j]=*(ip+i);
    printf("%d,",c[j]);
  }
  printf("\n");
//   // 8 -- strings
  printf("\n\n PART 8 ----------\n");
  printf("\n %s \n", AString);
  for(i=0;i<4;i++){
    printf("%d-",(int)AString[i]);
  }
  printf("\n");
  // last char is a 0 because it is a null char to show the end of the string
  for(i=0;i<4;i++){
    printf("%c-",(AString[i]+1));
  }
  // it prints IBM
  printf("\n");
  AString[3]= AString[3]+60;
  printf("%s \n", AString);
  //it prints HAL<

  // 9 -- address calculation
  ip = a;
  printf("\n\n PART 9 ----------\n");
  for (k = 0; k < 10; k++){
    b[k] = a[k]; 
    printf("Addy at %d is %x\n",k,&b[k]);
  }        // direct reference to array element

  ip = a;
  ip2 = b;
  for (k = 0; k < 10; k++){
    *ip2++ = *ip++; 
     printf("Addy at %d is %x\n",k,ip2); 
  }     // indirect reference to array element
  // not the same but I think is because i am reading in the second print statement affer is is incremented 
  // all done

  printf("\n\n ALL DONE\n");

  return 0;
 }