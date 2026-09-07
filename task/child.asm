.section .text
.globl _start

_start:
    # [child] lopeta heti (syscall 14)
    li    a7, 14
    .word 0x00800013

1:
    j     1b
