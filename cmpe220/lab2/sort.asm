	.data
A: 		.word 		5, 1, 4, 2, 8
new_line:	.asciiz 	"\n"

	.text
main:
	la $a0, A
	li $a1, 5
	jal sort
	
	li $t0, 0
	
print_loop:
	bge $t0, $a1, end_print_loop
	
	sll $t1, $t0, 2
	add $t2, $s1, $t1
	
	lw $a0, 0($t2)
	li $v0, 1
	syscall
	
	la $a0, new_line
	li $v0, 4
	syscall
	
	addi $t0, $t0, 1
	j print_loop
	
end_print_loop:
	li $v0, 10
	syscall
	
sort:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $s0, 0
	move $s1, $a0
	move $s2, $a1
	addi $s3, $s2, -1
	
outer_loop:
	bge $s0, $s2, end_sort
	add $s4, $s0, $zero
inner_loop:
	bge $s4, $s3, hop_to_outer
	
	sll $t0, $s4, 2
	add $a0, $s1, $t0
	lw $t2, 0($a0)
	addi $a1, $a0, 4
	lw $t3, 0($a1)
	
	ble $t2, $t3, end_inner_loop
	jal swap

end_inner_loop:
	addi $s4, $s4, 1
	j inner_loop
	
hop_to_outer:
	addi $s0, $s0, 1
	j outer_loop
	
end_sort:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	
	move $a0, $s1
	move $a1, $s2
	
	jr $ra
	
swap:
	lw $t0, 0($a0)
	lw $t1, 0($a1)
	sw $t1, 0($a0)
	sw $t0, 0($a1)
	
	jr $ra