CC=avr-gcc
OBJCOPY=avr-objcopy

TARGET=main
OBJECTS= main.o timer0.o
PORT=COM4

$(TARGET).hex:	$(TARGET).elf
	${OBJCOPY} -O ihex $(TARGET).elf $(TARGET).hex
	
$(TARGET).elf:	$(OBJECTS)
	${CC} -L "..\PLS7shield" -mmcu=atmega328p -o $(TARGET).elf $(OBJECTS) -l PLS7shield
	
%.o : %.c
	${CC} -Os -DF_CPU=16000000UL -mmcu=atmega328p -c $< -o $@
	
program: $(TARGET).hex
	avrdude -c arduino -p ATMEGA328P -P ${PORT} -U flash:w:$(TARGET).hex
	
clean:
	rm *.elf *.hex *.o