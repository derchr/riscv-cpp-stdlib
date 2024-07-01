.section .text
.globl _start

_start:
    la sp, _stack_top
    call __libc_init_array
    call main

.section .bss
.space 0x1000
_stack_top:
