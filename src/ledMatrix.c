#include "ledMatrix.h"
#include "systick.h"

static boardPin_t outputPins[] = {
	SR_CLOCK,
	SR_DATA_IN,
	SR_OUT_ENABLE_n,
	SR_LATCH,
	SR_RESET_n,
	LD_LATCH,
	LD_CLOCK,
	LD_DATA_IN,
	LD_OUT_ENABLE_n};

typedef struct
{
	boardPin_t clock;
	boardPin_t data;
	boardPin_t latch;
	boardPin_t outEnable_n;
	boardPin_t feedback;
} shiftreg_t;

shiftreg_t ShiftReg = {
	SR_CLOCK,
	SR_DATA_IN,
	SR_LATCH,
	SR_OUT_ENABLE_n,
	SR_FEEDBACK};

shiftreg_t LedDriver = {
	LD_CLOCK,
	LD_DATA_IN,
	LD_LATCH,
	LD_OUT_ENABLE_n,
	LD_FEEDBACK};

static int outputPinsSize = sizeof(outputPins) / sizeof(boardPin_t);

static void init_output_pins(void)
{
	for (int i = 0; i < outputPinsSize; i++)
	{
		init_pin(outputPins[i], OUTPUT);
	}
}

void init_led_matrix(void)
{
	init_output_pins();
	set_pin_state(LD_OUT_ENABLE_n, 0);
	set_pin_state(SR_OUT_ENABLE_n, 0);
	set_pin_state(SR_RESET_n, 1);
}

uint16_t DELAY_us = 20;

void load_shift_reg(uint8_t byte, shiftreg_t sr)
{
	for (int i = 0; i < 8; i++)
	{
		set_pin_state(sr.clock, 0);
		set_pin_state(sr.data, ((byte >> i) & 1));
		timer_delay(DELAY_us);
		set_pin_state(sr.clock, 1);
		timer_delay(DELAY_us);
	}
}

uint8_t matrix[8] = {
	0b00011000,
	0b00100100,
	0b01000010,
	0b10000001,
	0b10000001,
	0b01000010,
	0b00100100,
	0b00011000,
};

void update_matrix(void)
{
	uint8_t tmp = matrix[0];
	for (int i = 0; i < 7; i++)
	{
		matrix[i] = matrix[i + 1];
	}
	matrix[7] = tmp;
}

void load_matrix(uint8_t m[])
{

	for (int i = 0; i < 8; i++)
	{
		set_pin_state(LedDriver.latch, 0);
		set_pin_state(ShiftReg.latch, 0);

		load_shift_reg(1 << i, ShiftReg);
		load_shift_reg(m[i], LedDriver);

		set_pin_state(LedDriver.outEnable_n, 1);
		set_pin_state(ShiftReg.outEnable_n, 1);

		// timer_delay(DELAY_us);
		// timer_delay(500);
		// systick_delay(1000);
		set_pin_state(ShiftReg.latch, 1);
		set_pin_state(LedDriver.latch, 1);

		set_pin_state(LedDriver.outEnable_n, 0);
		set_pin_state(ShiftReg.outEnable_n, 0);
	}
}

void test(int on)
{
	load_matrix(matrix);
}

int ledOn = 1;
void blinky(timer_t *t)
{
	test(1);
}