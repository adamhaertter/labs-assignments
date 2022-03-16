	.data
new_line: 		.asciiz		"\n"
space_character: 	.asciiz 	" "
zero_double:		.double 	0.0

	.text
main: 
	li $v0, 5
	syscall
	move $s3, $v0	# rows A
	
	li $v0, 5
	syscall
	move $s4, $v0 	# cols A
	
	li $v0, 5
	syscall
	move $s5, $v0 	# row B
	
	li $v0, 5
	syscall
	move $s6, $v0 	# cols B
	
	addi $sp, $sp, -4
	
	move $a0, $s3
	move $a1, $s4
	jal allocate_space
	move $s0, $v0	# Start of A
	
	move $a0, $s5
	move $a1, $s6
	jal allocate_space
	move $s1, $v0 	# Start of B
	
	move $a0, $s3
	move $a1, $s6
	jal allocate_space
	move $s2, $v0	# Start of C
	
	move $a0, $s0
	move $a1, $s3
	move $a2, $s4
	jal read_in_elements
	
	move $a0, $s1
	move $a1, $s5
	move $a2, $s6
	jal read_in_elements
	
	jal mat_multiply
	
	move $a0, $s2
	move $a1, $s3
	move $a2, $s6
	jal display
	
	li $v0, 10
	syscall
	
allocate_space:
	mult $a0, $a1
	mflo $t1
	
	sll $t1, $t1, 3
	sub $v0, $sp, $t1
	sub $sp, $sp, $t1
	
	jr $ra
	
read_in_elements:	# $a0 = start of the array, $a1 = number rows, $a2 = number of cols
	li $t0, 0 	# index i
start_main_readin_loop:
	bge $t0, $a1, end_main_readin_loop
	
	li $t1, 0
start_inner_readin_loop:
	bge $t1, $a2, end_inner_readin_loop
	
	mult $t0, $a2
	mflo $t2
	
	add $t2, $t2, $t1
	sll $t2, $t2, 3
	
	add $t2, $t2, $a0
	
	li $v0, 7
	syscall
	
	s.d $f0, 0($t2)
	
	addi $t1, $t1, 1
	j start_inner_readin_loop
	
end_inner_readin_loop:
	addi $t0, $t0, 1
	j start_main_readin_loop
	
end_main_readin_loop:
	jr $ra

mat_multiply:
	li $t0, 0	# i
start_loop_i:
	bge $t0, $s3, end_loop_i
	
	li $t1, 0 	# j
start_loop_j:
	bge $t1, $s6, end_loop_j
	
	li $t2, 0 	# k
start_loop_k:
	bge $t2, $s4, end_loop_k
	
	mult $t0, $s4
	mflo $t3
	add $t3, $t3, $t2
	sll $t3, $t3, 3
	add $t3, $s0, $t3
	l.d $f2, 0($t3) 	# value of first[i][k] #CHANGED

	mult $t2, $s6
	mflo $t4
	add $t4, $t4, $t1
	sll $t4, $t4, 3
	add $t4, $s1, $t4	
	l.d $f4, 0($t4)	# value of second[k][j] #CHANGED
	
	mult $t0, $s6
	mflo $t5
	add $t5, $t5, $t1
	sll $t5, $t5, 3
	add $t5, $s2, $t5
	l.d $f6, 0($t5)	# value of result[i][j] #CHANGED
	
	mul.d $f8, $f2, $f4
	add.d $f6, $f6, $f8
	
	sdc1 $f6, 0($t5)
	
	addi $t2, $t2, 1
	j start_loop_k
	
end_loop_k:
	addi $t1, $t1, 1
	j start_loop_j
	
end_loop_j:
	addi $t0, $t0, 1
	j start_loop_i
	
end_loop_i:
	jr $ra
	
display:	# a0 = start of array, a1 = number of rows, a2 = number of cols
	move $t2, $a0
	move $t3, $a1
	move $t4, $a2

	li $t0, 0
display_loop_i_start:
	bge $t0, $a1, display_loop_i_end
	
	li $t1, 0
display_loop_j_start:
	bge $t1, $a2, display_loop_j_end

	mult $t0, $s6
	mflo $t5
	add $t5, $t5, $t1
	sll $t5, $t5, 3
	add $t5, $s2, $t5
	ldc1 $f12, 0($t5)
	
	li $v0, 3
	syscall
	
	la $a0, space_character
	li $v0, 4
	syscall

	addi $t1, $t1, 1
	j display_loop_j_start
display_loop_j_end:	
	la $a0, new_line
	li $v0, 4
	syscall

	addi $t0, $t0, 1
	j display_loop_i_start
display_loop_i_end:
	jr $ra
