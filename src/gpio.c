#include "stm32l011xx.h"
#include "gpio.h"

void init_pin(boardPin_t bp, pinMode_t pm){
	int moder_msk = 0x03 << (bp.pinNum * 2);
	int moder_mode = pm << (bp.pinNum *2);
	//TODO add in init gpio banks 
	bp.bank->MODER = (bp.bank->MODER & ~moder_msk) | moder_mode;
}

int get_pin_state(boardPin_t bp){
	return bp.bank->ODR & (0x1<<bp.pinNum);
}
void set_pin_state(boardPin_t bp, int value){
 	if(value)
		bp.bank->BSRR |= (0x1<<bp.pinNum);	
	else
		bp.bank->BSRR |= (0x1<<(bp.pinNum + 16)) ;	
}

