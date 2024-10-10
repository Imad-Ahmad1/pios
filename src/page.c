#include "page.h"
#include <stdint.h>
#include <stddef.h>


#define PAGE_SIZE 2048
#define NUM_PAGES 128


struct ppage *free_pages;
struct ppage *allocated_list;


struct ppage physical_page_array[NUM_PAGES];//array to hold physical pages 

void init_pfa_list(void){//initializes linked lists 
	for(int i = 0; i < NUM_PAGES; i++){ 
		physical_page_array[i].next = (i < NUM_PAGES -1) ? &physical_page_array[i+1] : NULL;
		physical_page_array[i].prev = (i > 0 ) ? &physical_page_array[i-1] : NULL;
		physical_page_array[i].physical_addr = (void *)((uintptr_t)physical_page_array + i * PAGE_SIZE);
	}
}
//allocated physical pages
struct ppage *allocate_physical_pages(unsigned int npages) { 
	struct ppage *allocated_list = NULL; 
	struct ppage *tail = NULL;

	for (unsigned int i = 0; i < NUM_PAGES && npages > 0; i++){
		struct ppage *page = &physical_page_array[i];

		if(page->next == NULL) break;//if there are no more pages 

		if(page->prev) page->prev->next = page->next;//unlinks page
		if(page->next) page->next->prev = page->prev; 

		//add to allocation
		page->next = NULL;
		if (!allocated_list) {
			allocated_list = page;//first page
		}else{
			tail->next = page; //link to next page 
			page->prev = tail;//set previous page 
		}
		tail = page;
		npages--;
	}
	return allocated_list;
}



void free_physical_pages(struct ppage *ppage_list) {
	struct ppage *current = ppage_list;

	while(current){
//links the page back 
		current->next = physical_page_array->next;
		if(physical_page_array->next){
			physical_page_array->next->prev = current;
		}

		physical_page_array->next = current;// update head of list 
		current->prev = NULL;//set previous
		current = current->next;//move to next page 
	}
}


