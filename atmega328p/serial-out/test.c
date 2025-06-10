/*
    Using example found here:
    https://www.appelsiini.net/2011/simple-usart-with-avr-libc/
*/
#include <avr/io.h> 
#include <stdio.h>

#define F_CPU 16000000UL
#define BAUD 9600

// util/setbaud provides helper macros for baud rate calculations.
//Requires F_CPU and BAUD to be defined first
#include <util/setbaud.h>

void uart_init(void) {
    UBRR0H = UBRRH_VALUE; // UBRR0H is the register for UART speed set to calculated value from setbaud.h
    UBRR0L = UBRRL_VALUE; // UBRR0L is the register for UART speed set to calculated value from setbaud.h

    //used to determine if UART has to be configured to run in double speed mode with given baud rate

    #if USE_2X
        UCSR0A |= _BV(U2X0);
    #else
        UCSR0A &= ~(_BV(U2X0));
    #endif


    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
    // With above bits we can set most common configuration: no parity, 8 data bits, 1 stop bit.
}

// void uart_putchar(char c) {
//     // You can transmit data to UART by writing a byte to USART Data Register UDR0

//     // First you have to make sure UART is ready to transmit new data.
//     // You can wait until USART Data Register Empty UDRE flag is set.
//     loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
//     UDR0 = c;
// }

// // void uart_putchar(char c) {
// //    UDR0 = c;

// //    // Alternatively you can wait after each byte to transmission be ready. USART Transmit Complete TXC0 is set when transmission is ready
// //    loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
// // }

// char uart_getchar(void) {
//     // You can receive data from UART by reading a byte from USART Data Register UDR0

//     // USART Receive Complete RXC0 flag is set if to unread data exists in data register    
//     loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
//     return UDR0;
// }




void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}


// Save the In and Out Stream of data as a file which allows for a buffer to be used to display all the data

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

// this allows one file to show in and out
//FILE uart_io FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW)







int main(void) {

    uart_init();
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








