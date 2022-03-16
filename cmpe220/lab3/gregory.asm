.data

sum: .double 0.0
denom: .double 1.0
f: .double 0.0
one: .double 1.0
four: .double 4.0 
addingDenom: .double 2.0
prompt: .asciiz "Enter number of terms: "
result: .asciiz "Pi is " 

.text

main: 
li $v0, 4
la $a0, prompt
syscall

li $v0, 5 
la $a0, 5
syscall 

move $a0, $v0           #ready for function call... 

jal gregory

mov.d $f12, $f0
li $v0, 3
syscall 


li $v0, 10
syscall


gregory:

#what we have to do here... is make sure we allocate room in the stack for the pointer 
addi $sp, $sp, -12
sw $ra, ($sp)   #store the stack pointer. 
sw $a0, 8($sp)


l.d $f20, sum 
l.d $f22, denom 
l.d $f24, f

addi $t0, $t0, 0 


functionLoopTop: 
lw $t1, 8($sp) 
lw $t0, 4($sp)   #bring i back. 

bge $t0, $t1, functionEnd

LoopInside:
l.d $f26, one 
div.d $f24, $f26, $f22 

addi $a0, $t0, 0
sw $t0, 4($sp) 
sw $t1, 8($sp)
jal isEven
lw $t0, 4($sp)
lw $t1, 8($sp)



beq $v0, 1, whenEven
beq $v0, 0, whenOdd

whenEven:

add.d $f20, $f20, $f24
j loopEnd

whenOdd:
sub.d $f20, $f20, $f24
j loopEnd

loopEnd:
addi $t0, $t0, 1
l.d $f4, addingDenom
add.d $f22, $f22, $f4
sw $t0, 4($sp)

j functionLoopTop 

functionEnd:
l.d $f24, four

mul.d $f0, $f24, $f20 
lw $ra, ($sp)
addi $sp, $sp, 12
jr $ra



isEven: 

andi $t0, $a0, 0x01
beq $t0, 1, ifodd
beq $t0, 0, ifeven

ifodd: 
li $v0, 0
j end

ifeven:
li $v0, 1
j end 

end: 

jr $ra 

