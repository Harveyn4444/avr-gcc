/*
https://github.com/mattwach/avr_pico/blob/main/examples/blink_attiny85/main.c
*/
//#define F_CPU 16500000UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define PIN 6

int main(void) {
  DDRB = 1 << PIN;
  while (1) {
    PORTB = 1 << PIN;
    _delay_ms(2000);
    PORTB = ~(1 << PIN);
    _delay_ms(1000);
  }
}
