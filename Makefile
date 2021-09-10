# Compiler settings. Only edit CFLAGS to include other header files.
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -Wall -Werror
CFLAGS += -mthumb -march=armv7-m
CFLAGS += -ffreestanding
CFLAGS += -Iapps -Ios -Iperip

# Assembler flags
ASFLAGS = -Ios

# Linker options
LDFLAGS = -nostdlib -Tlinker.ld

vpath %.c apps os perip startup stdlib
vpath %.s os
vpath %.h apps os perip

all: sos.elf
	$(OBJCOPY) -O ihex sos.elf sos.hex
	$(OBJCOPY) -O binary sos.elf sos.bin

sos.elf: startup.o main.o gpio.o rcc.o uart.o os.o apps.o terminal.o armv7-m.o
sos.elf: printf.o memory.o thread_list.o
	$(LD) $(LDFLAGS) $^ -o sos.elf

clean:
	rm -f *.o sos.elf sos.hex sos.bin

# Flash the STM32F4
flash:
	st-flash --reset write sos.bin 0x08000000
