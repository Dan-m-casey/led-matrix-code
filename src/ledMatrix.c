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
	boardPin_t outEnable;
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

void set_shift_reg(uint8_t byte, shiftreg_t sr)
{
	set_pin_state(sr.latch, 0);

	for (int i = 0; i < 8; i++)
	{
		set_pin_state(sr.clock, 0);
		set_pin_state(sr.data, ((byte >> i) & 1));
		systick_delay(20);
		set_pin_state(sr.clock, 1);
		systick_delay(20);
	}
	set_pin_state(sr.latch, 1);
}

void test(int on)
{
	set_shift_reg(on, LedDriver);
	set_shift_reg(on, ShiftReg);
}

int ledOn = 1;
void blinky(timer_t *t)
{
	if (is_timer_expired(*t))
	{
		reset_timer(t);
		ledOn = !ledOn;
		test(ledOn);
	}
}