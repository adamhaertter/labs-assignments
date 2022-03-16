	.data
A:	.word 		100
B:	.word		200
C:	.word		300

	.text
main:
    la $t0, A
    lw $t1, 0($t0)
    la $t2, B
    lw $t3, 0($t2)
    sw $t1, 4($t0)
    