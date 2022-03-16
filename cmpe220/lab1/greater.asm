	.data
prompt:		.asciiz 	"Enter two numbers: "
alb: 		.asciiz 	"A is less than B\n"
aeb: 		.asciiz 	"A is equal to B\n"
agb: 		.asciiz 	"A is greater than B\n"

	.text
main: 
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	
	li $v0, 5
	syscall
	move $t1, $v0
	
	blt $t0, $t1, ifALB
	beq $t0, $t1, ifAEB
	bgt $t0, $t1, ifAGB
	
ifALB:
	la $a0, alb
	li $v0, 4
	syscall
	j exit

ifAEB:
	la $a0, aeb
	li $v0, 4
	syscall
	j exit

ifAGB:
	la $a0, agb
	li $v0, 4
	syscall
	j exit

exit:
	li $v0, 10
	syscall