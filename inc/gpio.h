#ifndef __GPIO_H__
#define __GPIO_H__
#include "stm32l011xx.h"

typedef enum
{
    INPUT,
    OUTPUT,
    ALTERNATE,
    ANALOG
} pinMode_t;

typedef struct
{
    GPIO_TypeDef *bank;
    int pinNum;
} boardPin_t;

extern void init_pin(boardPin_t bp, pinMode_t pm);
extern int get_pin_state(boardPin_t bp);
extern void set_pin_state(boardPin_t bp, int value);

#endif
