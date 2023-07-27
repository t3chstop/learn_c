#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linked_list.h"



#if 1
int main() {
	//Set up free and allocated linked lists
	node_t* free = NULL;
	node_t* allocated = NULL;

	void* head = malloc(1024);

	addSorted(&free, head, 1024);



	return 0;
}
#endif

void* allocate(unsigned int size) {
	//Search in free list for smallest chunk that will fulfill request
}