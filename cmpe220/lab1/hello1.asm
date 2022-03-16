	.data
prompt:	.asciiz		"Enter your name:"
hello:	.asciiz		"hello "
meet: 	.asciiz 	",pleased to meet you!\n"
name: 	.space 32

	.text
main:
    la	$a0, prompt
    li  $v0, 4
    syscall
    
    la $a0, name
    li $a1, 32
    li $v0, 8
    syscall
    
    la $a0, hello
    li $v0, 4
    syscall
    
    la $a0, name
    syscall
    
    la $a0, meet
    syscall
    
    li $v0, 10
    syscall
