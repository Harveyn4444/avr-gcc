# Tools
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

# MCU and clock
MCU=atmega328p
F_CPU=16000000UL

# Source and target
SRC=main.c
TARGET=main

# Upload configuration
PROGRAMMER=arduino
PORT=/dev/ttyUSB0
BAUD=57600    # Nano with old bootloader often needs 57600 baud for upload

# Flags
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
AVRDUDE_FLAGS=-c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -D

# Default target: build hex file
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

# Mark phony targets
.PHONY: all upload clean
