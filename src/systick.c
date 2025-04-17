#include "stm32l011xx.h"
#include "systick.h"

volatile uint32_t MSCount = 0;

void SysTick_Handler(void)
{
	MSCount += 10;
}

uint32_t get_ms_count(void)
{
	return MSCount;
}

void init_systick(void)
{
	MSCount = 0;
	SysTick->LOAD = 0x0004e200;
	SysTick->CTRL = 0x00000007;
}

/*Blocking delay*/
void systick_delay(int ms)
{
	int delay = get_ms_count() + ms;
	while (delay > get_ms_count())
		;
}

void init_tim2()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Configure TIM2
	TIM2->CNT = 0;
	TIM2->PSC = 0;
	TIM2->ARR = 0xffff;
	TIM2->CR1 |= TIM_CR1_CEN; // Start timer
}

/* System clock runs at 32000000
TIM2 gets its clock from system clock.
32 clock cycles = 1us */
void timer_delay(uint16_t microSeconds)
{
	TIM2->CNT = 0;
	int delay = microSeconds * 32;

	while (TIM2->CNT < delay)
		;
}