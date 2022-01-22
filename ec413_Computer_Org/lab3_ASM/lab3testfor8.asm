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

        la      $a0,Enter      # address of string to print
        li      $v0,4           # system call code for print_str
        syscall

        add $t3,$t3,1 # increment counter 
        blt $t3,$t4, PrintRows      
Exit:
	jr $ra