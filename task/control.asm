.section .text
.globl _start

_start:
    # Testiketju: 11 -> 11 -> 14 -> 14
    # control(1)->control(11)->hello(11)->hello(14)->control(1)

    # [control] merkki alkuun
    li    a7, 1
    .word 0x00800013

    # [control] spawn hello.bin (syscall 11)
.Lhello_ptr:
    auipc a0, %pcrel_hi(hello_name)
    addi  a0, a0, %pcrel_lo(.Lhello_ptr)
    li    a7, 11
    .word 0x00800013
.Lprint_ptr:
    # Jos exit-paluuketju toimii, tänne palataan hello.bin:n jälkeen
    auipc a0, %pcrel_hi(hello_name)
    addi  a0, a0, %pcrel_lo(.Lprint_ptr)
    li    a7, 2
    .word 0x00800013

1:
    j     1b

hello_name:
    .asciz "hello.bin"
