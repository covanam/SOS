# source files
SRCS=main.c gpio.c rcc.c os.c armv7-m.s uart.c startup.c terminal.c apps.c\
     printf.c thread_list.c memory.c

# Binaries will be generated with this name (.elf, .bin, .hex)
PROJ_NAME=sos

# Compiler settings. Only edit CFLAGS to include other header files.
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -Wall -Werror -Tlinker.ld
CFLAGS += -mthumb -march=armv7-m
CFLAGS += -nostdlib -ffreestanding

# object files
OBJS = $(SRCS:.c=.o)

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
flash:
	st-flash --reset write $(PROJ_NAME).bin 0x08000000
