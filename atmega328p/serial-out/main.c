#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL  // 16 MHz clock
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

// Initialize USART0
void uart_init(void) {
    // Set baud rate
    UBRR0H = (UBRR_VALUE >> 8);
    UBRR0L = UBRR_VALUE;

    // Enable transmitter
    UCSR0B = (1 << TXEN0);

    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Send a single byte
void uart_send_byte(uint8_t data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into buffer, sends the data
    UDR0 = data;
}

// Send a string
void uart_send_string(const char *str) {
    while (*str) {
        uart_send_byte(*str++);
    }
}

int main(void) {
    uart_init();

    while (1) {
        uart_send_string("Hello, World!\r\n");
        _delay_ms(1000);
    }
}
