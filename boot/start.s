.section .text.boot, "ax"

.equ STACK_BASE, 0x10074

.global _start

_start:                         
    li   t6, STACK_BASE
    li   t5, 0
    add  sp, t6, t5
    j    init

