#include "stm32l011xx.h"
#include "systick.h"
#include "timers.h"
#include "pll.h"
#include "gpio.h"

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


#define BOARD_LED		(boardPin_t){GPIOB, 3}




int main(void){
	timer_t blinky = {0};
	init_pll();
	init_systick();
	
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER &= ~(0x000000C0);
	GPIOB->MODER |=  GPIO_MODER_MODE3_0; 
	
	GPIOB->BSRR |= GPIO_BSRR_BS_3;
	
	init_pin(BOARD_LED,OUTPUT);
	
	set_pin_state(BOARD_LED,1);
	set_pin_state(BOARD_LED,0);

	set_timer(&blinky,100);
	
	while(1){
		if(is_timer_expired(blinky)){	
			reset_timer(&blinky);

			if(get_pin_state(BOARD_LED)){
				set_pin_state(BOARD_LED,0);
			}
			else{
				set_pin_state(BOARD_LED,1);
 			}
		}
	}	
}
