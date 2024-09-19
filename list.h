

//define linked list structure
struct list_element {
	struct list_element *next;//points to next elemenet
	void *data;//points to the data

};

//put list together
void list_add(struct list_element **head, struct list_element *new_element);
void list_remove(struct list_element **head, struct list_element *element_to_remove);

