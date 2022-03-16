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
	
	and $t2, $t0, $t1
	or $t3, $t0, $t1
	xor $t4, $t0, $t1
	
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, result
	li $v0, 4
	syscall
	
	move $a0, $t3
	li $v0, 1
	syscall
	la $a0, result
	li $v0, 4
	syscall
	
	move $a0, $t4
	li $v0, 1
	syscall
	la $a0, result
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall