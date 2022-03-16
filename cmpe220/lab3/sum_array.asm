.data

a: .float  0:20                     
prompt: .asciiz "Enter the number of elements, up to 20: "
total:  .asciiz "Total: "
newline: .asciiz "\n"
s:       .float 0
sum:     .float 0

.text

main:

li $s0, 0               #n
li $s1, 0               #i

while: 
                                #there's a short-circuit OR here. this means we need to test both if and only if the first condition is false. As such...
condition: 
ble $s0, 0, ifportion                      
ble $s0, 20, loop1end

ifportion:         

la $a0, prompt                  #load address of prompt
li $v0, 4                       #load syscall 4 into v0. prints String
syscall

li $v0, 5                       #loads syscall code 5 into v0, will read integer. 
syscall

move $s0, $v0                   #move v0 into s0-- will represent n. 

j condition                     #jump to condition-- which repeats loop.


loop1end: 

secondloop:                    #second loop will adjust address of array, and then prompts input to insert values into the array one at a time. 
bge $s1, $s0, endsecondloop    #when i reaches n, the loop ends. 
addi $t0, $s1, 0               #temporary register = i to serve as array alignment. 
#establish
la $t1, a                      #load address of array into t1. 
sll $t0, $t0, 2                #multiply i by 4
add $t0, $t0, $t1              #add it to memory to get offset.  


li $v0, 6                      #load 6 into v0. this will read a floating-point number. 
syscall 
swc1 $f0, ($t0)                #store this floating-point into array at address i.
addi $s1, $s1, 1               #i++

j secondloop

endsecondloop:

la $a0, a                     #load address of a into argument 0.
move $a1, $s0                 #move n over to be argument 1. 
jal sum_array                 #invoke function sum_array


la $a0, total                 #load the total string into a0 to print it
li $v0, 4                     #designate syscall argument v0 for print string. 
syscall 


li $v0, 2                    #load the syscall argument v0 for print_float
mov.s $f12, $f1              #move the result of calculation into f12 to print
syscall                      

la $a0, newline              #ends by loading newline into a0 
li $v0, 4                    #syscall 4-- designated print_string. 
syscall

end:
li $v0, 10                   #syscall exit code. End of program. 
syscall


sum_array:                   #sum array function 

li $t0, 0                    #local variable i. 

func_loop:
bge $t0, $a1, endfuncloop    #condition i < n
addi $t1, $t0, 0             #make a copy of i for alignment again. 

#align. 
sll $t1, $t1, 2              #multiply by 4(floats take up 4 bytes)
add $t2, $a0, $t1            #t2 is now the proper address.
lwc1 $f22, ($t2)             #load float from aligned address. 
add.s $f23, $f22, $f23       #add f23 by f22 + f23-- it'll accumulate. 


addi $t0, $t0, 1             #i++

j func_loop

endfuncloop:
mov.s $f1, $f23              #move result to return value via the calling convention. 

jr $ra                       #jump back to main. 







  



