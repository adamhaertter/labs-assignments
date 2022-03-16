	.data
prompt:		.asciiz 	"How many stars? "
star: 		.asciiz 	"*"
new_line:	.asciiz		"\n"

	.text
main:
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0

	li $s1, 0
loop:
	bge $s1, $s0, end
	
	move $a0, $s1
	jal stars
	
	addi $s1, $s1, 1
	
	j loop
	
end:
	li $v0, 10
	syscall
	
stars:
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	
	li $t0, 0
	move $t1, $a0
	
loop_stars:
	bgt $t0, $t1, stars_end
	
	la $a0, star
	li $v0, 4
	syscall
	
	addi $t0, $t0, 1
	
	j loop_stars
	
stars_end:
	la $a0, new_line
	syscall
	
	lw $a0, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra