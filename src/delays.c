unsigned long get_timer_count() {
	unsigned long *timer_count_register = (long unsigned int*)0x3f003004;
	return *timer_count_register;
}

void wait_msec(int m) {
	unsigned long tmp = get_timer_count();
	while(1){
		if(get_timer_count() >= tmp + (m*1000)) break;
	}
}
void wait_cycles(int t) {
	unsigned long tmp = get_timer_count();
	while(1) {
		if (get_timer_count() >= tmp + t) break;
	}
}
