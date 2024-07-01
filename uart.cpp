#include "uart.h"

#include <sys/_stdint.h>

static const uintptr_t* UART0_CTRL_ADDR = (uintptr_t*)0x10000000;

int uart_putchar(int ch)
{
    return *(char*)UART0_CTRL_ADDR = ch & 0xff;
}
