	.data
prompt_text: 	.asciiz		"Enter text: "
prompt_size:	.asciiz 	"Enter size of box: "
star: 		.asciiz 	"*"
star_space:	.asciiz 	"* "
space_star:	.asciiz 	" *\n"
new_line: 	.asciiz 	"\n"

input_string: 	.space 		32

	.text
main:
	la $a0, prompt_text
	li $v0, 4
	syscall
	
	la $a0, input_string
	li $a1, 32
	li $v0, 8
	syscall
	
	la $a0, prompt_size
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0
	
	move $a0, $s0
	jal stars
	
	la $a0, input_string
	jal print_words
	
	move $a0, $s0
	jal stars
	
	li $v0, 10
	syscall
	
stars:
	move $t0, $a0

stars_loop:
	ble $t0, $zero, exit_stars
	
	la $a0, star
	li $v0, 4
	syscall
	
	addi $t0, $t0, -1
	
	j stars_loop
	
exit_stars: 
	la $a0, new_line
	li $v0, 4
	syscall
	
	jr $ra

print_words:
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	
	la $a0, star_space
	li $v0, 4
	syscall
	
	lw $t0, 0($sp)
	
print_words_loop:
	lb $t1, 0($t0)
	beq $t1, 0x0a, end_loop_print_words
	
	addi $t0, $t0, 1
	
	j print_words_loop
	
end_loop_print_words:
	sb $zero, 0($t0)
	
	lw $t0, 0($sp)
	la $a0, 0($t0)
	li $v0, 4
	syscall
	
	la $a0, space_star
	li $v0, 4
	syscall
	
	lw $a0, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra
