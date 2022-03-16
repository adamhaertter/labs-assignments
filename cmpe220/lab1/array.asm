	.data
prompt: .asciiz 	"Enter a number: "
array: 	.word		1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010
result: .asciiz 	"\n"

	.text
main: 
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	
	addi $t0, $t0, -1
	sll $t1, $t0, 2
	
	la $t2, array
	add $t3, $t2, $t1
	lw $t4, 0($t3)
	
	move $a0, $t4
	li $v0, 1
	syscall
	la $a0, result
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall