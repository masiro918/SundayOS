.extern timer_count

.equ MMIO_BASE,         0x200000
.equ ADDR_TIMER_ENABLE, (MMIO_BASE + 0x24)

.global timer_handler
timer_handler:
    la      t0, timer_count
    lw      t1, 0(t0)
    addi    t1, t1, 1
    sw      t1, 0(t0)
    ret

/*
 * Timer interrupt handler address is fixed by emulator,
 * so no CSR setup is needed here.
 */

.globl enable_interrupts
enable_interrupts:
    li      t0, ADDR_TIMER_ENABLE
    li      t1, 1
    sb      t1, 0(t0)
    ret

.global disable_interrupts
disable_interrupts:
    li      t0, ADDR_TIMER_ENABLE
    sb      zero, 0(t0)
    ret

.global init_machine_timer_interrupt
init_machine_timer_interrupt:
    li      t0, ADDR_TIMER_ENABLE
    li      t1, 1
    sb      t1, 0(t0)
    ret



