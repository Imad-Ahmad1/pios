#include "list.h"
#include <stdio.h>


long buf[256]; 


struct obj {
	struct obj *next; // 8 bytes
	int payload1;    // 4 bytes
	int payload2;    // 4 bytes

};


//head begins buf[0]
int main() {

	
	
        struct obj *pObj =(struct obj*)& buf[4]; 	
	struct obj *pObj2 = (struct obj*)& buf[6]; 

	long*ptr = &buf[4];
	pObj->next = &buf[6];
	pObj->payload1 = 0xdeadbeef;
	pObj->payload2 = 0xbeefcafe;

	pObj2 = buf[6];
	pObj->next = &buf[7];
	
	
	pObj->next->next;

	
	//head = pObj;
	//buf[4] = buf[7];


	printf("sizeof(myObj) = %ld\n", sizeof(pObj));

	for(int k =0;k <10;k++){
	printf("[%d @ %p] 0x%lx\n",k,&buf[k], buf[k]);
	}
	return 0;


}

