#ifndef __GPIO_H__
#define __GPIO_H__

typedef enum {
	INPUT,
	OUTPUT,
	ALTERNATE,
	ANALOG
} pinMode_t;

typedef struct {
	GPIO_TypeDef* bank;
	int pinNum;
} boardPin_t;

void init_pin(boardPin_t bp, pinMode_t pm);

int get_pin_state(boardPin_t bp);
void set_pin_state(boardPin_t bp, int value);

#endif

