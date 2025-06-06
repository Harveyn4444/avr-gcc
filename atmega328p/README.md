Compiling in terminal without Makefile

```
$ avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c

$ avr-gcc -mmcu=atmega328p main.o -o main

$ avr-objcopy -O ihex -R .eeprom main main.hex

$ avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 57600 -U flash:w:main.hex

```

* Note the baud rate is `57600` as this is the required baud rate for the "old bootloader" variant for Arduino/Arduino Nano (Which uses the Atmega328p).