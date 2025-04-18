#include "gpio.h"
#include "ledMatrix.h"
#include "pll.h"
#include "stm32l011xx.h"
#include "systick.h"
#include "timers.h"

uint8_t test_matrix[] = {
	0b00011000,
	0b00100100,
	0b01000010,
	0b10000001,
	0b10000001,
	0b01000010,
	0b00100100,
	0b00011000,
	0b00000000,

};

void update_matrix(void)
{
	uint8_t tmp = test_matrix[0];
	for (int i = 0; i < 7; i++)
	{
	    test_matrix[i] = test_matrix[i + 1];
	}
	test_matrix[7] = tmp;
}


int main(void)
{
    timer_t blink_timer = {0};
    timer_t update_matrix_timer = {0};
    timer_t load_matrix_timer = {0};

    set_timer(&blink_timer, 1000);

    //TODO calc refresh rate
    //@60hz
    //16ms = 1/60
    //TODO update timer for us
    //won't be accurate
    set_timer(&load_matrix_timer, 16);

    set_timer(&update_matrix_timer, 100);

    init_pll();
    init_systick();
    init_tim2();

    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
    GPIOB->MODER &= ~(0x000000C0);
    GPIOB->MODER |= GPIO_MODER_MODE3_0;

    GPIOB->BSRR |= GPIO_BSRR_BS_3;

    init_pin(BOARD_LED, OUTPUT);

    set_pin_state(BOARD_LED, 1);
    set_pin_state(BOARD_LED, 0);

    init_led_matrix();
    while (1)
    {
        //This is writing the data matix out to the hardware led matrix
        if(is_timer_expired(load_matrix_timer)){
            reset_timer(&load_matrix_timer);
            load_matrix(test_matrix);
        }


        //this updates the data matrix
        if (is_timer_expired(update_matrix_timer)){
            reset_timer(&update_matrix_timer);
            update_matrix();
        }

        //this is on board led - neucleo
        if (is_timer_expired(blink_timer))
        {
            reset_timer(&blink_timer);
            set_pin_state(BOARD_LED, !get_pin_state(BOARD_LED));
        }
    }
}
