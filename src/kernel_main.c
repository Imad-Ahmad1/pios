#include <stdint.h>
#include "rprintf.c"
#include "serial.c"
#include "fat.h"  

extern int __bss_start, __bss_end;

void clear_bss() {
    char *bss_start = (char *)&__bss_start;
    char *bss_end = (char *)&__bss_end;

    while (bss_start < bss_end) {
        *bss_start++ = 0;
    }
}

unsigned long get_timer_count();
void timerprob();

int sd_readblock(unsigned int lba, unsigned char *buffer, unsigned int num) {
        return 0;
}

void kernel_main() {
    clear_bss();
    fatInit();
    fatOpen();
    fatRead();
  
   
    unsigned long timercounter = get_timer_count();
    timerprob();
    timercounter = get_timer_count();
}
unsigned long get_timer_count() {
    unsigned long *timer_count_register = (unsigned long *)0x3f003004;
    return *timer_count_register;
}

void timerprob() {
    unsigned long tmp = get_timer_count();
    while (1) {
        if (get_timer_count() >= tmp + 1000) break;
    }
}
