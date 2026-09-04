.section .trapvec, "ax"

.globl ecall_trap_handler
.globl timer_trap_handler

ecall_trap_handler:
    j trap_ecall
    nop

timer_trap_handler:
    j trap_timer

.section .text, "ax"

.extern interrupt_handler

trap_ecall:
    .word 0x00900013   # custom mret

trap_timer:
    addi    sp, sp, -120

    # Save GPRs that can be clobbered by C handler call.
    sw      ra, 0(sp)
    sw      gp, 4(sp)
    sw      tp, 8(sp)
    sw      t0, 12(sp)
    sw      t1, 16(sp)
    sw      t2, 20(sp)
    sw      s0, 24(sp)
    sw      s1, 28(sp)
    sw      a0, 32(sp)
    sw      a1, 36(sp)
    sw      a2, 40(sp)
    sw      a3, 44(sp)
    sw      a4, 48(sp)
    sw      a5, 52(sp)
    sw      a6, 56(sp)
    sw      a7, 60(sp)
    sw      s2, 64(sp)
    sw      s3, 68(sp)
    sw      s4, 72(sp)
    sw      s5, 76(sp)
    sw      s6, 80(sp)
    sw      s7, 84(sp)
    sw      s8, 88(sp)
    sw      s9, 92(sp)
    sw      s10, 96(sp)
    sw      s11, 100(sp)
    sw      t3, 104(sp)
    sw      t4, 108(sp)
    sw      t5, 112(sp)
    sw      t6, 116(sp)

    call    interrupt_handler

    # Restore registers and return from interrupt.
    lw      ra, 0(sp)
    lw      gp, 4(sp)
    lw      tp, 8(sp)
    lw      t0, 12(sp)
    lw      t1, 16(sp)
    lw      t2, 20(sp)
    lw      s0, 24(sp)
    lw      s1, 28(sp)
    lw      a0, 32(sp)
    lw      a1, 36(sp)
    lw      a2, 40(sp)
    lw      a3, 44(sp)
    lw      a4, 48(sp)
    lw      a5, 52(sp)
    lw      a6, 56(sp)
    lw      a7, 60(sp)
    lw      s2, 64(sp)
    lw      s3, 68(sp)
    lw      s4, 72(sp)
    lw      s5, 76(sp)
    lw      s6, 80(sp)
    lw      s7, 84(sp)
    lw      s8, 88(sp)
    lw      s9, 92(sp)
    lw      s10, 96(sp)
    lw      s11, 100(sp)
    lw      t3, 104(sp)
    lw      t4, 108(sp)
    lw      t5, 112(sp)
    lw      t6, 116(sp)

    addi    sp, sp, 120
    .word 0x00900013   # custom mret

.globl do_context_switch
do_context_switch:
    sw ra, 0(a0)
    sw sp, 4(a0)
    sw s0, 8(a0)
    sw s1, 12(a0)
    sw s2, 16(a0)
    sw s3, 20(a0)
    sw s4, 24(a0)
    sw s5, 28(a0)
    sw s6, 32(a0)
    sw s7, 36(a0)
    sw s8, 40(a0)
    sw s9, 44(a0)
    sw s10, 48(a0)
    sw s11, 52(a0)
    lw ra, 0(a1)
    lw sp, 4(a1)
    lw s0, 8(a1)
    lw s1, 12(a1)
    lw s2, 16(a1)
    lw s3, 20(a1)
    lw s4, 24(a1)
    lw s5, 28(a1)
    lw s6, 32(a1)
    lw s7, 36(a1)
    lw s8, 40(a1)
    lw s9, 44(a1)
    lw s10, 48(a1)
    lw s11, 52(a1)
    ret
