.section .text
.globl _start

_start:
    # setup default trap vector
    la t0, trap_vector
    csrw mtvec, t0

    la sp, _stack_top
    call __libc_init_array
    call main
    call _exit

    .align 2
trap_vector:
    mv      a0, sp
    csrr    a1, mcause
    csrr    a2, mepc
    jal     trap_handler
    mret

.section .bss
.space 0x1000
_stack_top:
