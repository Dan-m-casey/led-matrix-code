#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__
#include "gpio.h"
#include "timers.h"

#define SR_LATCH (boardPin_t){GPIOA, 6}
#define SR_DATA_IN (boardPin_t){GPIOA, 2}
#define SR_CLOCK (boardPin_t){GPIOA, 5}
#define SR_OUT_ENABLE_n (boardPin_t){GPIOA, 7}
#define SR_RESET_n (boardPin_t){GPIOA, 4}
#define SR_FEEDBACK (boardPin_t){GPIOA, 3}

#define LD_LATCH (boardPin_t){GPIOB, 4}
#define LD_CLOCK (boardPin_t){GPIOB, 5}
#define LD_DATA_IN (boardPin_t){GPIOA, 11}
#define LD_OUT_ENABLE_n (boardPin_t){GPIOA, 8}
#define LD_FEEDBACK (boardPin_t){GPIOB, 1}

#define BOARD_LED (boardPin_t){GPIOB, 3}

extern void init_led_matrix(void);
extern void blinky(timer_t *t);
extern void update_matrix(void);
extern void load_matrix(uint8_t byte[]);

#endif
