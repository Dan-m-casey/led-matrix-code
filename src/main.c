#include "gpio.h"
#include "ledMatrix.h"
#include "pll.h"
#include "stm32l011xx.h"
#include "systick.h"
#include "timers.h"

int main(void)
{
    timer_t blink_timer = {0};
    timer_t sr_timer = {0};
    set_timer(&blink_timer, 1000);
    set_timer(&sr_timer, 1000);

    init_pll();
    init_systick();

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
        blinky(&sr_timer);

        if (is_timer_expired(blink_timer))
        {
            reset_timer(&blink_timer);

            if (get_pin_state(BOARD_LED))
            {
                set_pin_state(BOARD_LED, 0);
            }
            else
            {
                set_pin_state(BOARD_LED, 1);
            }
        }
    }
}
