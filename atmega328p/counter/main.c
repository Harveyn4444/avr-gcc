#include "uart.h"  // bring in UART function declarations
#include "config.h"  // bring in declared BAUD rate and CPU frequency - to change them edit config.h
#include <util/delay.h>


int main(void) {

    uart_init();
    fflush(stdout);
    stdout = &uart_output;
    stdin  = &uart_input;

    char input;
    unsigned int counter = 0;
    fflush(stdout);

    while(1) {
        printf("Hello World %d !\n", counter);
        fflush(stdout);
        _delay_ms(1000);
        counter++;
    }

    return 0;
}