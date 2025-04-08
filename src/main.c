#include "stm32l011xx.h"

typedef struct {
	GPIO_TypeDef* bank;
	int pinNum;
} boardPin_t;

#define SR_LATCH		(boardPin_t){GPIOA, 6}
#define SR_DATA_IN		(boardPin_t){GPIOA, 2}
#define SR_CLOCK		(boardPin_t){GPIOA, 5}
#define SR_OUT_ENABLE_n	(boardPin_t){GPIOA, 7}
#define SR_RESET_n		(boardPin_t){GPIOA, 4}
#define SR_FEED_BACK	(boardPin_t){GPIOA, 3}

#define LD_LATCH		(boardPin_t){GPIOB, 4}
#define LD_CLOCK		(boardPin_t){GPIOB, 5}
#define LD_DATA_IN		(boardPin_t){GPIOA, 11}
#define LD_OUT_ENABLE_n	(boardPin_t){GPIOA, 8}
#define LD_FEED_BACK	(boardPin_t){GPIOB, 1}


/* Systick stuff start */

volatile int MSCount = 0;

void SysTick_Handler(void){
	MSCount += 10;
}

void init_systick(void){
	MSCount = 0;
	SysTick->LOAD = 0x0004e200;
	SysTick->CTRL = 0x00000007;
}
/* Systick stuff end*/


/*Timer stuff start */

typedef struct {
	uint32_t timestamp_set;
	uint32_t timestamp_expire;
} timer_t;


int is_timer_expired(timer_t t){
	return MSCount > t.timestamp_expire;
}

void set_timer(timer_t* t, int milliseconds){
	t->timestamp_set = milliseconds;
	t->timestamp_expire = MSCount + milliseconds;
}	

void reset_timer(timer_t* t){
	t->timestamp_expire = (MSCount + 1000);
}

/*Timer stuff end*/

/* PLL stuff start */
void init_pll(void){
    FLASH->ACR |= FLASH_ACR_LATENCY;    //set latency to one wait state per word read
 	RCC->CFGR |= RCC_CFGR_PLLDIV2;      //set PLL devider to 2
    RCC->CFGR |= RCC_CFGR_PLLMUL4;      //set PLL multiplier to 4
    RCC->CR |= RCC_CR_HSION;            //Enable HSI clock
    while(!(RCC->CR & RCC_CR_HSIRDY));    //spin till HSI RDY flag set
    RCC->CR |= RCC_CR_PLLON;            //Enable PLL Clock
    while(!(RCC->CR & RCC_CR_PLLRDY));    //spin till PLL RDY flag set
	RCC->CFGR |= RCC_CFGR_SW_PLL;    
}
/*PLL stuff end */

int main(void){
	volatile int i = 0;
	timer_t blinky = {0};
	init_pll();

	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(0x000000C0);
	GPIOB->MODER |=  GPIO_MODER_MODE3_0; 
	
	init_systick();
	GPIOB->BSRR |= GPIO_BSRR_BS_3;
	
	while(1){
		if(is_timer_expired(blinky)){
			
			reset_timer(&blinky);
			if(GPIOB->ODR & 0x00000008){
				GPIOB->BSRR |= GPIO_BSRR_BR_3;
			}
			else{
				GPIOB->BSRR |= GPIO_BSRR_BS_3;
 			}
		}
	}	
}
