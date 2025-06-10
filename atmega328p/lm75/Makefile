# MCU and clock frequency
MCU = atmega328p
F_CPU = 16000000UL

# Compiler and flags
CC = avr-gcc
# CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable


# Source files
SRCS = main.c

# Object files (replace .c with .o) for the same name
OBJS = $(SRCS:.c=.o)

# Output file
TARGET = main.elf
# -------------

# AVR tools for programming (optional)
AVRDUDE = avrdude
AVRDUDE_FLAGS = -c arduino -P /dev/ttyUSB0 -b 57600 -p $(MCU)  # adjust programmer

# Default target
all: $(TARGET)

# Link object files to create final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile C source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Flash to device (optional, change programmer and port as needed)
flash: $(TARGET)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(TARGET):e

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all flash clean



