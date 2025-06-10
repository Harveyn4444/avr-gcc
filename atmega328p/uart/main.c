#include "uart.h"  // bring in UART function declarations
#include "config.h"  // bring in declared BAUD rate and CPU frequency - to change them edit config.h

// #define F_CPU 16000000UL
// #define BAUD 9600

int main(void) {

    uart_init();
    //This connect the basic functions of puts() and getChar() directly to the UART data
    // So calling this puts or reads from the UART hardware too.
    stdout = &uart_output;
    stdin  = &uart_input;

    char input;

    while(1) {
        puts("Hello world!");
        input = getchar();
        printf("You wrote %c\n", input);
    }

    return 0;
}