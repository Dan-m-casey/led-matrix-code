#ifndef __TIMERS_H__
#define __TIMERS_H__

typedef struct {
	uint32_t timestamp_set;
	uint32_t timestamp_expire;
} timer_t;

int is_timer_expired(timer_t t);

void set_timer(timer_t* t, int milliseconds);

void reset_timer(timer_t* t);

#endif 
