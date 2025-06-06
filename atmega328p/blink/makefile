# MCU and clock
MCU=atmega328p
F_CPU=16000000UL

# Programmer and upload port
PROGRAMMER=arduino
# PORT=/dev/ttyACM0
PORT=/dev/ttyUSB0
# BAUD=115200
BAUD=57600

# Files
SRC=main.c
TARGET=main

# Tools
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

# Flags
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
AVRDUDE_FLAGS=-c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -D

# Default target
all: $(TARGET).hex

# Build ELF from C
$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Build HEX from ELF
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload to microcontroller
upload: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<:i

# Clean up
clean:
	rm -f *.elf *.hex

# Mark targets that aren't real files
.PHONY: all upload clean
