	.data
prompt: 	.asciiz 	"My God! Its full of how many stars?: "
star: 		.asciiz		"*"
newLine: 	.asciiz		"\n"

	.text
main: 
	la $a0, prompt
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	
	j loop
	
loop:
	ble $t0, $zero, exit
	
	la $a0, star
	li $v0, 4
	syscall
	
	addi $t0, $t0, -1
	
	j loop
	
exit: 
	la $a0, newLine
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall