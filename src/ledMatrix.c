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


//TODO: should this be a calucated number
uint16_t DELAY_us = 20;



/* 20us per delay
 *
 * 40us per bit
 *
 * 8*40us = 320us per byte
 * 320us * 9 = 2880us  or 2.8ms
 * each frame is on for 2.8ms at full speed
 *
 *
 *
 * */
//byte level
void load_shift_reg(uint8_t byte, shiftreg_t sr)
{
    for (int i = 0; i < 8; i++)
    {
        //set clock low
        set_pin_state(sr.clock, 0);
        //set data
        set_pin_state(sr.data, ((byte >> i) & 1));
        //pre delay
        timer_delay(DELAY_us);
        //set clock high
        set_pin_state(sr.clock, 1);
        //post delay
        timer_delay(DELAY_us);
    }
}


void load_matrix(uint8_t m[])
{

    for (int i = 0; i < 9; i++)
    {
        //Latch down
        set_pin_state(LedDriver.latch, 0);
        set_pin_state(ShiftReg.latch, 0);


        //this could be made more efficient by doing both at the same time
        //set data line
        load_shift_reg(1 << i, ShiftReg);
        load_shift_reg(m[i], LedDriver);

        //Latch up
        set_pin_state(ShiftReg.latch, 1);
        set_pin_state(LedDriver.latch, 1);
    }
}

