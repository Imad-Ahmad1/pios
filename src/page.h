#ifndef PAGE_H 
#define PAGE_H 


struct ppage { 
	struct ppage *next;
	struct ppage *prev; 
	void *physical_addr;
};



void init_pfa_list(void); //initializes free page list 
struct ppage *allocate_physical_pages(unsigned int npages); //function to allocate physical pages 
void free_physical_pages(struct ppage *ppage_list);//function to free allocated pages



#endif // PAGE_H


