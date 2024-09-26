
<<<<<<< HEAD
#include "rprintf.c"
#include "serial.c"
=======
#include <stdint.h> //standard integer 
		    

extern int __bss_start, __bss_end;
//represents start and end 

void clear_bss() { //clear bss
	char *bss_start = (char *)&__bss_start; //pointers for start and end
	char *bss_end = (char *)&bss_end;

	while(bss_start < bss_end) {
		*bss_start++ = 0; //sets each byte to 0 
	}
}




char glbl[128];

char huge_array[8192];
>>>>>>> origin/main



char glbl[128];

char huge_array[8192];

unsigned long get_timer_count();
void timerprob();

void kernel_main() {

<<<<<<< HEAD
char thing[] = "helloworld";
esp_printf(putc, "%s", thing);




=======
	clear_bss();
>>>>>>> origin/main

	extern int __bss_start, __bss_end;
	char *bssstart, *bssend;

	bssstart = &__bss_start;
	bssend = &__bss_end;


<<<<<<< HEAD
	unsigned long timercounter = get_timer_count();
	timerprob();
	timercounter = get_timer_count();



=======


    while(1){
    }
>>>>>>> origin/main
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
