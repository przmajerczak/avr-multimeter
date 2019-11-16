MCU=atmega16
CC=avr-gcc
OBJCOPY=avr-objcopy
CC_FLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU}
OBJCOPY_FLAGS=-j .text -j .data -O ihex 
PROG=usbasp
OBJFILES=main.o display.o utilities.o
TARGET=main

all: ${TARGET}.hex
	
main.o: main.c
	${CC} ${CC_FLAGS} -c main.c -o main.o

display.o: display.c display.h
	${CC} ${CC_FLAGS} -c display.c -o display.o

utilities.o: utilities.c utilities.h
	${CC} ${CC_FLAGS} -c utilities.c -o utilities.o

${TARGET}.hex: ${OBJFILES}
	${CC} ${CC_FLAGS} -o ${TARGET}.elf ${OBJFILES}
	${OBJCOPY} ${OBJCOPY_FLAGS} ${TARGET}.elf ${TARGET}.hex

clean:
	rm -f *.o *.elf *.hex

flash:
	avrdude -p ${MCU} -c ${PROG} -U flash:w:${TARGET}.hex:i