MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/tty.usbmodem11101
BAUD = 115200
TARGET = main

all: $(TARGET).hex

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

%.elf: %.c
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -o $@ $<

flash: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -p $(MCU) -U flash:w:$(TARGET).hex:i

clean:
	rm -f *.hex *.elf
