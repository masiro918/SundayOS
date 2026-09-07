.section .text
.globl _start

_start:
    # [hello] spawn child.bin (toinen syscall 11 ketjussa)
.Lchild_ptr:
    auipc a0, %pcrel_hi(hello)
    addi  a0, a0, %pcrel_lo(.Lchild_ptr)
    li    a7, 2
    .word 0x00800013

    # [hello] child palasi exitillä, nyt hello exit (syscall 14)
    li    a7, 14
    .word 0x00800013

1:
    j     1b

hello:
    .asciz "Hello world!\n"
