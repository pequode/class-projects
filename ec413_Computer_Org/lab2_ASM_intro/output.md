3). The output was "The sorted array is\n 1234"
5). Memory starts at: 0x00400000
	The address of msg is:0x10010010 
	The variable count is at:10010020
6).What’s happening?: the program is creating the peramaters for a for loop then it loads in each element of the array sequentially and compairs it to the next element with subtraction. if the number is less than zero it keeps them the same by jumping over the swap instructions. and not setting them to false

   Observe the values being loaded into the array in the data segment as you step through the program:
   What are the new array values?:	 it is intializes from 5, 7, 4, 3 to 4,3,2,1 in the initilization step then the order changes as follows:
   4321
   3421
   3241
   3214
   2314
   2134
   1234
8).
5, 7, 4, 3
00000003  00000004  00000002  00000001 
00000003  00000002  00000004  00000001 
00000003  00000002  00000001  00000004
etc...
bassically this: except is would break a bunch of times on false positivies and have the same number 
   4321
   3421
   3241
   3214
   2314
   2134
   1234

10).
00000005  00000007  00000004  00000003
00000003  00000004  00000002  00000001
00000003  00000000  00000004  00000001 
00000003  00000000  00000001  00000004 
00000000  00000003  00000001  00000004  
00000000  00000001  00000003  00000004   

12).
00000001  00000002  00000003  00000004  00000005  00000006  00000007  00000008