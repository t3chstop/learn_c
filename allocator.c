#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linked_list.h"



#if 1

void* allocate(node_t* free, node_t* allocated, unsigned int size);

int main() {
	//Set up free and allocated linked lists
	node_t* free = NULL;
	node_t* allocated = NULL;

	void* head = malloc(1024);

	addFirst(&free, head, 1024);

	printf("%p\n", allocate(&free, &allocated, 17));
	printf("%p\n", allocate(&free, &allocated, 12));
	printf("%p\n", allocate(&free, &allocated, 21));

	//addSorted(&allocated, NULL, 12);
	//addSorted(&allocated, NULL, 30);
	//addSorted(&allocated, NULL, 12);

	print(free);
	printf("\n");
	print(allocated);

	return 0;
}
#endif

void* allocate(node_t** free, node_t** allocated, unsigned int size) {
	//Search in free list for smallest chunk that will fulfill request
	node_t* locationNode = smallestLocation(*free, size);
	void* location = locationNode->ptr;

	//Update free list
	if (locationNode->size - size < 8) {
		//Delete node
		delete(*free, locationNode);
	}
	else {
		//Edit the node
		if (size % 8 == 0) {
			(char*)locationNode->ptr += size;
			locationNode->size -= size;
		}
		else {
			(char*)locationNode->ptr += size + (8-size%8);
			locationNode->size -= size + (8 - size % 8);
		}
	}

	addSorted(allocated, location, size);
	return location;
}

void* free(node_t** free, node_t** allocated, void* location) {
	//Update allocated list
	delete(allocated, location);


}