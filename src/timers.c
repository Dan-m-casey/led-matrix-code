#include "stm32l011xx.h"
#include "systick.h"
#include "timers.h"

int is_timer_expired(timer_t t){
	return get_ms_count() > t.timestamp_expire;
}

void set_timer(timer_t* t, int milliseconds){
	t->timestamp_set = milliseconds;
	t->timestamp_expire = get_ms_count() + milliseconds;
}	

void reset_timer(timer_t* t){
	t->timestamp_expire = (get_ms_count() + t->timestamp_set);
}
