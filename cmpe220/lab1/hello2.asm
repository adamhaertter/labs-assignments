	.data
prompt: 	.asciiz 	"Enter your name: "
name: 		.space 		32
hello: 		.asciiz 	"Hello "
meetMsg: 	.asciiz 	", pleased to meet you.\n"

	.text
main: 
	la $a0, prompt
	li $v0, 4
	syscall
	
	la $a0, name
	li $a1, 32
	li $v0, 8
	syscall

	li $t0, 0
	j loop
	
loop:
	la $t1, name
	add $t3, $t1, $t0
	lbu $t4, 0($t3)
	
	beq $t4, 0x00, exit
	beq $t4, 0x0a, ifEqualNL
	
	addi $t0, $t0, 1
	j loop
	
ifEqualNL:
	sb $zero, 0($t3)
	j loop

exit:
	la $a0, hello
	li $v0, 4
	syscall
	
	la $a0, name
	syscall
	
	la $a0, meetMsg
	syscall
	
	li $v0, 10
	syscall