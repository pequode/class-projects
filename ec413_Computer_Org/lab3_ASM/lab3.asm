############################################################################
#                       Lab 3
#                       EC413
#
#    		Assembly Language Lab -- Programming with Loops.
#
############################################################################
#  DATA
############################################################################
        .data           # Data segment
OutCount: .word 42
Hello:  .asciiz " \n Hello World! \n "  # declare a zero terminated string
Hello_len: .word 16
testout:   .asciiz "d"
AnInt:	.word	12		# a word initialized to 12
space:	.asciiz	" "	# declare a zero terminate string
WordAvg:   .word 0		#use this variable for part 4
ValidInt:  .word 0		#
ValidInt2: .word 0		#
lf:     .byte	10, 0	# string with carriage return and line feed
InLenW:	.word   4       # initialize to number of words in input1 and input2
InLenB:	.word   16      # initialize to number of bytes in input1 and input2
        .align  4
Input1:	.word	0x01020304, 0x05060708
	.word	0x090A0B0C, 0x0D0E0F10
        .align  4
Input2: .word   0x01221117, 0x090b1d1f   # input
        .word   0x0e1c2a08, 0x06040210
        .align  4
Copy:  	.space  0x80    # space to copy input word by word
        .align  4
 
Enter: .asciiz "\n\n"
Comma: .asciiz ","
############################################################################
#  CODE
############################################################################
        .text                   # code segment
#
# print out greeting
#
main:
        la	$a0,Hello	# address of string to print
        li	$v0,4		# system call code for print_str
        syscall                 # print the string

	
#Code for Item 2
#Count number of occurences of letter "l" in Hello string
        

        la  $t0,Hello # loads hell0 
        li $t1,0 #set ofset amount
        li $t6,0 #counter of l  

        lw $t5,Hello_len #just in case loop turns infinate




        lb $t3,5($t0)# used to get the l char 
CheckDone:
        lb $t2,0($t0)# current char 
        # if statement
        bne $t3,$t2,EndOfIf
        addi $t6,$t6,1 # add 1 to counter 
EndOfIf: 
        add $t0,$t0,1 # increase offset
        add $t1,$t1,1 # increase offset
        blt $t1,$t5,CheckDone
        sw $t6,OutCount

        move      $a0,$t6       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall     



################################################################################
        la      $a0,Enter       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall  
################################################################################

#
# Code for Item 3 -- 
# Print the integer value of numbers from 0 and less than AnInt
#

        li      $v0,1           # system call code for print_str

        li $t0,0  #value to print 
        lw $t1,AnInt #value to go to
CountToTwv:
        move      $a0,$t0       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall     
        la      $a0,Enter       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall  
        add $t0,$t0,1 
        blt $t0,$t1,CountToTwv

###################################################################################
        la	$a0,Enter	# address of string to print
        li	$v0,4		# system call code for print_str
        syscall                 # print the string
###################################################################################
#
# Code for Item 4 -- 
# Print the integer values of each byte in the array Input1 (with spaces)
#
        la $t0,Input1# starting addy of array
        li $t1,0 # set up the loop could probably use t0 but idk if it changes
        lw $t2,InLenB   # set stopping point at inlenw
NEXTELL:
        lb $t4,0($t0) # get val to display
        move      $a0,$t4      # address of string to print
        li      $v0,1           # system call code for print_str
        syscall     
        la      $a0,space       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall                 # print the string
        add $t0,$t0,1
        add $t1,$t1,1
        blt $t1,$t2,NEXTELL

###################################################################################
        la      $a0,Enter       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall                 # print the string
###################################################################################
#
# Code for Item 5 -- 
# Write code to copy the contents of Input2 to Copy
#       
        la $t0,Input1# starting addy of array
        la $t3,Input2# starting addy of array
        li $t1,0 # set up the loop could probably use t0 but idk if it changes
        lw $t2,InLenW 
NEXTInd:
        lw $t4,0($t0) # copy the value of input1[i] into a reg
        sw $t4,0($t3)# save that reg into input2[i]

        move      $a0,$t4       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall     

        la      $a0,Comma       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall

        move    $a0,$t4       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall   

        la      $a0,space       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall
                         # print the string
        add $t0,$t0,4 # index the array of input 1 
        add $t3,$t3,4 # do same for input 2 
        add $t1,$t1,1 # index loop counter 1 
        blt $t1,$t2,NEXTInd

#################################################################################
        la	$a0,Enter	# address of string to print
        li	$v0,4		# system call code for print_str
        syscall                 # print the string
###################################################################################
#
# Code for Item 6 -- 
# Print the minimum, maximum, and integer average of the contents of array Input1
#       
        la $t0,Input1 # start of input 
        lw $t1, 0($t0) # min
        lw $t5, 0($t0) # max initial 
        li $t3,0        # loop counter
        li $t6,0 # running quotent sum 
        li $t7,0 # temp quotent 
MinMaxLoop:
        lw $t4,0($t0) # current word 

        blt $t4,$t1,DoneMin
        move $t1,$t4    # assign min as new number 
DoneMin:
        bgt $t4,$t5,DoneMax
        move $t1,$t4    # assign max as new number 
DoneMax:
        
        div $t4,$t2 # take the division of current num by InLenW
        mflo $t7 # take quotent put it in t7 
        add $t6,$t6,$t7 # add this quotent to the running average/ not as accurate as a sum and then div but keeps sum small
        add $t0,$t0,4 # increare element         
        add $t3,$t3,1 # increase counter
        blt $t3,$t2,MinMaxLoop
# min
        move    $a0,$t1       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall   

        la      $a0,Comma       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall
# max 
        move    $a0,$t5       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall   

        la      $a0,Comma       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall
# average 
        move    $a0,$t6       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall   


#################################################################################
        la	$a0,Enter	# address of string to print
        li	$v0,4		# system call code for print_str
        syscall                 # print the string
##################################################################################
#
# Code for Item 7 -- 
# Display the first 30 integers that are divisible by either 7 and 13 (with comma)
#

        li $t0,0 # number to print 
        li $t1,7 # multiple of seven 
        li $t2,13 # multiple of 13 
        li $t3,0 # counter 
        li $t4,30 # max number of indexs 
PrintFirst30:
        move    $a0,$t0       # address of string to print
        li      $v0,1           # system call code for print_str
        syscall   
        la      $a0,Comma       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall
        blt $t1,$t2,SevenWasLess
        j ThirteenwasLess
SevenWasLess:
        move $t0,$t1 #assign print num to the smaller of the two numbers 
        add $t1,$t1,7 #add 1 of itself and then go to end of loop 
        j Doneifs
ThirteenwasLess: 
        move $t0,$t2 #assign print num to the smaller of the two numbers 
        add $t2,$t2,13 #add 1 of itself and then go to end of loop 
        j Doneifs
Doneifs:
        add $t3,$t3,1 # increment counter 
        blt $t3,$t4, PrintFirst30       
#################################################################################
        la      $a0,Enter       # address of string to print
        li      $v0,4           # system call code for print_str
        syscall                 # print the string
##################################################################################
#
# Code for Item 8 -- 
# Repeat step 7 but display the integers in 6 lines with 5 integers with spaces per line
# This must be implemented using a nested loop.
#
        li $t0,0 # number to print 
        li $t1,7 # multiple of seven 
        li $t2,13 # multiple of 13 
        li $t3,0 # row counter 
        li $t4,6 # max number of rows 
        li $t5,0 # collom counter 
        li $t6,5 # max number of collom 
PrintRows:

        printCols:
                move    $a0,$t0       # address of string to print
                li      $v0,1           # system call code for print_str
                syscall   
                la      $a0,space      # address of string to print
                li      $v0,4           # system call code for print_str
                syscall

                blt $t1,$t2,SevenWasLez
                j ThirteenwasLez
                SevenWasLez:
                        move $t0,$t1 #assign print num to the smaller of the two numbers 
                        add $t1,$t1,7 #add 1 of itself and then go to end of loop 
                        j Doneif
                ThirteenwasLez: 
                        move $t0,$t2 #assign print num to the smaller of the two numbers 
                        add $t2,$t2,13 #add 1 of itself and then go to end of loop 
                        j Doneif

        Doneif:
                add $t5,$t5,1 # increment counter 
                blt $t5,$t6, printCols    
        li $t5,0        
        la      $a0,Enter      # address of string to print
        li      $v0,4           # system call code for print_str
        syscall

        add $t3,$t3,1 # increment counter 
        blt $t3,$t4, PrintRows      
Exit:
	jr $ra