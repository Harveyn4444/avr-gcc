/*
 * LM75A temperature readout over I2C
 * Output temperature over UART at 9600 baud
 * Target: ATmega328P (e.g. Arduino Nano)
 */

#define F_CPU 16000000UL  // 16 MHz clock
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

#define LM75A_ADDRESS 0x48  // 7-bit I2C address

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>  // for dtostrf()

/* Initialize USART */
void USART_init() {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    UCSR0B = (1 << TXEN0);                         // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);        // 8-bit data
}

/* Send single byte over USART */
void USART_send(char data) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for empty buffer
    UDR0 = data;
}

/* Send string over USART */
void USART_sendString(const char *str) {
    while (*str) {
        USART_send(*str++);
    }
}

/* Initialize TWI (I2C) */
void TWI_init() {
    TWSR = 0x00;  // Prescaler = 1
    TWBR = 72;    // SCL frequency ~100 kHz @16 MHz
}

/* Send START condition */
void TWI_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

/* Send STOP condition */
void TWI_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

/* Write data byte */
void TWI_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

/* Read byte with ACK */
uint8_t TWI_readAck() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/* Read byte with NACK */
uint8_t TWI_readNack() {
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/* Read temperature from LM75A and convert to float */
float readTemperature() {
    uint8_t msb, lsb;
    int16_t rawTemp;

    // Start transmission and select temperature register (0x00)
    TWI_start();
    TWI_write((LM75A_ADDRESS << 1) | 0);  // Write mode
    TWI_write(0x00);                      // Temperature register

    // Repeated start for read
    TWI_start();
    TWI_write((LM75A_ADDRESS << 1) | 1);  // Read mode

    // Read MSB and LSB
    msb = TWI_readAck();
    lsb = TWI_readNack();
    TWI_stop();

    // 11-bit temperature: MSB + upper 3 bits of LSB
    rawTemp = ((msb << 8) | lsb) >> 5;

    // Sign extend if negative
    if (rawTemp & (1 << 10)) {
        rawTemp |= 0b1111100000000000;
    }

    // Convert to Celsius (0.125 °C resolution)
    return rawTemp * 0.125;
}

int main(void) {
    char buffer[16];
    float temperature;

    USART_init();
    TWI_init();

    while (1) {
        temperature = readTemperature();

        // Format temperature as string with 2 decimal places
        dtostrf(temperature, 5, 2, buffer);

        // Send over UART
        // USART_sendString("Temperature: ");
        // USART_sendString(buffer);
        // USART_sendString(" C\r\n");

        USART_sendString(buffer);
        USART_sendString("\n");


        _delay_ms(1000);  // 1-second delay
    }
}
