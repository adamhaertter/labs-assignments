	.data
prompt: 		.asciiz 	"Enter a number: "
is_even: 		.asciiz 	"It is even"
is_odd: 		.asciiz 	"It is odd"

	.text
main:
	jal read_number
	
	move $a0, $v0
	jal print_evenodd
	
	li $v0, 10
	syscall

read_number:
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	
	jr $ra
	
print_evenodd:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	jal isodd
	
	beqz $v0, if_even
	
	la $a0, is_odd
	li $v0, 4
	syscall
	
	j end_print_evenodd
	
if_even:
	la $a0, is_even
	li $v0, 4
	syscall
	
end_print_evenodd:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra
	
isodd:
	andi $v0, $a0, 0x01
	jr $ra