#include "stm32l011xx.h"

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

