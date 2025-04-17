#ifndef __SYSTICK_H__
#define __SYSTICK_H__

extern void init_systick(void);

extern uint32_t get_ms_count(void);
extern void systick_delay(int ms);
extern void init_tim2(void);
extern void timer_delay(uint16_t microSeconds);

#endif
