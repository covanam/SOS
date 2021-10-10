# Compiler settings. Only edit CFLAGS to include other header files.
CC=../build/gcc.sh
AS=arm-none-eabi-as
LD=../build/ld.sh
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -Wall -Wextra -Werror -Os
CFLAGS += -I../perip -I../sys

vpath %.c ../stdlib ../build ../perip ../sys
vpath %.s ../sys

all: app.elf
	$(OBJCOPY) -O ihex app.elf app.hex
	$(OBJCOPY) -O binary app.elf app.bin

app.elf: terminal.o gpio.o uart.o startup.o mutex.o thread.o sos.o apps.o
app.elf: printf.o memory.o
	$(LD) $(LDFLAGS) $^ -o app.elf

clean:
	rm -f *.o app.elf app.hex app.bin
