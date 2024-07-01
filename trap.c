#include <cstdlib>
#include <stdio.h>
#include <sys/_stdint.h>

extern "C" void trap_handler(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
    printf("machine mode: unhandlable trap %lu @ 0x%lx\n", mcause, mepc);
    exit(-1);
}
