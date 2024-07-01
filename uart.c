// Copyright (c) 2013, The Regents of the University of California (Regents).
// Copyright (c) 2018-2019, The libfemto authors
// All Rights Reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the Regents nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.

// IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
// OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
// HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
// MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

#include "uart.h"

#include <sys/_stdint.h>

#define UART0_CLOCK_FREQ 1843200
#define UART0_BAUD_RATE 115200
#define NS16550A_UART0_CTRL_ADDR 0x10000000
#define SIFIVE_TEST_CTRL_ADDR 0x100000

enum
{
    UART_RBR = 0x00, /* Receive Buffer Register */
    UART_THR = 0x00, /* Transmit Hold Register */
    UART_IER = 0x01, /* Interrupt Enable Register */
    UART_DLL = 0x00, /* Divisor LSB (LCR_DLAB) */
    UART_DLM = 0x01, /* Divisor MSB (LCR_DLAB) */
    UART_FCR = 0x02, /* FIFO Control Register */
    UART_LCR = 0x03, /* Line Control Register */
    UART_MCR = 0x04, /* Modem Control Register */
    UART_LSR = 0x05, /* Line Status Register */
    UART_MSR = 0x06, /* Modem Status Register */
    UART_SCR = 0x07, /* Scratch Register */

    UART_LCR_DLAB = 0x80, /* Divisor Latch Bit */
    UART_LCR_8BIT = 0x03, /* 8-bit */
    UART_LCR_PODD = 0x08, /* Parity Odd */

    UART_LSR_DA = 0x01, /* Data Available */
    UART_LSR_OE = 0x02, /* Overrun Error */
    UART_LSR_PE = 0x04, /* Parity Error */
    UART_LSR_FE = 0x08, /* Framing Error */
    UART_LSR_BI = 0x10, /* Break indicator */
    UART_LSR_RE = 0x20, /* THR is empty */
    UART_LSR_RI = 0x40, /* THR is empty and line is idle */
    UART_LSR_EF = 0x80, /* Erroneous data in FIFO */
};

static volatile uint8_t* uart;

void ns16550a_init()
{
    uart = (uint8_t*)(void*)NS16550A_UART0_CTRL_ADDR;
    uint32_t uart_freq = UART0_CLOCK_FREQ;
    uint32_t baud_rate = UART0_BAUD_RATE;
    uint32_t divisor = uart_freq / (16 * baud_rate);
    uart[UART_LCR] = UART_LCR_DLAB;
    uart[UART_DLL] = divisor & 0xff;
    uart[UART_DLM] = (divisor >> 8) & 0xff;
    uart[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

int ns16550a_getchar()
{
    if (uart[UART_LSR] & UART_LSR_DA)
    {
        return uart[UART_RBR];
    }
    else
    {
        return -1;
    }
}

int ns16550a_putchar(int ch)
{
    while ((uart[UART_LSR] & UART_LSR_RI) == 0)
        ;
    return uart[UART_THR] = ch & 0xff;
}
