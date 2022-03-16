	.data
prompt:	  .asciiz		"Enter two numbers: "
result:   .asciiz		"\n"

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
	
	add $t2, $t0, $t1
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	la $a0, result
	li $v0, 4
	syscall

	li $v0, 10
	syscall
