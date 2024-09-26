
#include "rprintf.c"
#include "serial.c"



char glbl[128];

char huge_array[8192];

unsigned long get_timer_count();
void timerprob();

void kernel_main() {

char thing[] = "helloworld";
esp_printf(putc, "%s", thing);





	extern int __bss_start, __bss_end;
	char *bssstart, *bssend;

	bssstart = &__bss_start;
	bssend = &__bss_end;


	unsigned long timercounter = get_timer_count();
	timerprob();
	timercounter = get_timer_count();



}

unsigned long get_timer_count () {
unsigned long * timer_count_register = 0x3f003004 ;
 return * timer_count_register ;
 }

void timerprob(){
	unsigned long tmp = get_timer_count();
    while(1){
	    if(get_timer_count() >= tmp + 1000) break;
    }
} 
