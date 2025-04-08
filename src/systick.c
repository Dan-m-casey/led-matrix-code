#include "stm32l011xx.h"

volatile uint32_t MSCount = 0;

void SysTick_Handler(void){
	MSCount += 10;
}

uint32_t get_ms_count(void){
	return MSCount;
}

void init_systick(void){
	MSCount = 0;
	SysTick->LOAD = 0x0004e200;
	SysTick->CTRL = 0x00000007;
}
