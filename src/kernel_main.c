
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



void kernel_main() {

	clear_bss();

	extern int __bss_start, __bss_end;
	char *bssstart, *bssend;

	bssstart = &__bss_start;
	bssend = &__bss_end;




    while(1){
    }
}
