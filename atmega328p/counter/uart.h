#ifndef UART_H
#define UART_H

#include <stdio.h>

// Initialize UART (baud rate defined via macros)
void uart_init(void);

// Send a character via UART
void uart_putchar(char c);

// Receive a character via UART
char uart_getchar(void);


FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

#endif // UART_H