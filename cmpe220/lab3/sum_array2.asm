.data


#this time, we have a new task. We have to NOT add things up when they're below 0
#this means the code can remain the same for the most part, but we have to 
#make a few minor adjustments. 

a: .float 0:20                     
prompt: .asciiz "Enter the number of elements, up to 20: "
total:  .asciiz "Total: "
newline: .asciiz "\n"
sum:     .float 0
compare: .float 0 

.text

main:

li $s0, 0               #n
li $s1, 0               #i

while: 
#there's a short-circuit OR here. this means we need to test both-- and ignore If and only if
#both conditions prove false. 

condition: 
ble $s0, 0, ifportion
ble $s0, 20, loop1end

ifportion:

la $a0, prompt
li $v0, 4
syscall

li $v0, 5
syscall

move $s0, $v0

j condition


loop1end: 

secondloop:
bge $s1, $s0, endsecondloop
addi $t0, $s1, 0
#establish
la $t1, a 
sll $t0, $t0, 3  #multiply i by 8
add $t0, $t0, $t1 #add it. 


li $v0, 6
syscall 
swc1 $f0, ($t0)
addi $s1, $s1, 1

j secondloop

endsecondloop:

la $a0, a
move $a1, $s0
jal sum_array


la $a0, total
li $v0, 4
syscall 

#then, print the float total
li $v0, 2
mov.s $f12, $f1
syscall

la $a0, newline
li $v0, 4 
syscall

li $v0, 10
syscall


sum_array:

li $t0, 0       #i
swc1 $f24, compare

func_loop:
bge $t0, $a1, endfuncloop
addi $t1, $t0, 0

#align. 
sll $t1, $t1, 3
add $t2, $a0, $t1    #t2 is now the proper address.
lwc1 $f22, ($t2)

c.lt.s $f22, $f24
bc1t increment

add.s $f23, $f22, $f23

increment:
addi $t0, $t0, 1

j func_loop

endfuncloop:
mov.s $f1, $f23

jr $ra 