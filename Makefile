CMSIS = CMSIS
SRC = src
INC = inc
APPNAME = led-matrix-test

SOURCES = \
    $(CMSIS)/startup_stm32l011xx.S \
    $(CMSIS)/system_stm32l0xx.c\
    $(SRC)/main.c\
    $(SRC)/systick.c\
    $(SRC)/ledMatrix.c\
    $(SRC)/timers.c\
    $(SRC)/gpio.c\
    $(SRC)/pll.c\


LDSCR = $(CMSIS)/ARMCMx.ld

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as

CDEF = -nostartfiles -DSTM32L011xx -I $(CMSIS) -I $(INC) -T $(LDSCR) -mcpu=cortex-m0plus


$(APPNAME).bin: $(APPNAME).elf
	arm-none-eabi-objcopy -O binary $(APPNAME).elf $(APPNAME).bin

$(APPNAME).elf: $(SOURCES)
	$(CC) $(CDEF) $(SOURCES) -Wall -o $(APPNAME).elf

$(APPNAME).hex: $(APPNAME).elf
	arm-none-eabi-objcopy -O ihex $(APPNAME).elf $(APPNAME).hex

$(APPNAME).dmp: $(APPNAME).elf
	$(PREFIX)objdump --disassemble-all $(APPNAME).elf > $(APPNAME).dmp

.PHONY: clean

clean:
	rm $(APPNAME).elf $(APPNAME).hex $(APPNAME).dmp *.bin *.i
