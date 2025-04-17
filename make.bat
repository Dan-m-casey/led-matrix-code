@echo off

rem When using windows this batch file will act as a simulated make file.  

echo making bin file

set INCLUDES=-I inc\ -I CMSIS\

rem the carat ^ is for continuing a new line 
  
set SOURCES=^
	src\main.c ^
	CMSIS\startup_stm32l011xx.S ^
	CMSIS\system_stm32l0xx.c ^
	src\systick.c ^
	src\timers.c ^
	src\pll.c ^
	src\gpio.c ^
	src\ledMatrix.c

set LINKSCR=CMSIS\ARMCMx.ld

arm-none-eabi-gcc.exe -nostartfiles -mcpu=cortex-m0plus -Os -DSTM32L011xx %INCLUDES% %SOURCES% -T %LINKSCR% -o test.elf

arm-none-eabi-objcopy.exe -O binary test.elf test.bin

