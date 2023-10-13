#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linked_list.h"



#if 1

void* allocate(node_t* free, node_t* allocated, unsigned int size);
void freeLoc(node_t** free, node_t** allocated, void* location);

int main() {
	//Initialize randomizer
	srand(time(NULL));

	//Set up free and allocated linked lists
	node_t* free = NULL; 
	node_t* allocated = NULL;


	unsigned int TOTAL_SIZE = 2048;
	void* head = malloc(TOTAL_SIZE);
	addFirst(&free, head, TOTAL_SIZE);

	//Make allocations in array
	void* arr[100];
	int i;
	arr[0] = allocate(&free, &allocated, 11);
	for (i = 1; i < 100; i++) {
		arr[i] = allocate(&free, &allocated, rand() % 20);
		printf("%d\n", (char*)arr[i] - arr[i - 1]);
	}

	//Free half of the locations
	for (i = 0; i < 50; i++) {
		freeLoc(&free, &allocated, arr[rand() % 100]);
	}

	print(free);
	printf("\n");
	print(allocated);


	return 0;


	//void* alloc1 = allocate(&free, &allocated, 17);
	//void* alloc2 = allocate(&free, &allocated, 21);
	//void* alloc3 = allocate(&free, &allocated, 12);


	//printf("%p\n", alloc1);
	//printf("%p\n", alloc2);
	//printf("%p\n", alloc3);

	//printf("\n");
	//print(free);
	//printf("\n");
	//print(allocated);
	//printf("\n");

	//freeLoc(&free, &allocated, alloc2);

	//printf("\n");
	//print(free);
	//printf("\n");
	//print(allocated);

	//return 0;
}
#endif

void* allocate(node_t** free, node_t** allocated, unsigned int size) {
	//Search in free list for smallest chunk that will fulfill request
	node_t* locationNode = smallestLocation(*free, size);
	void* location = locationNode->ptr;

	//Update free list
	if (locationNode->size - size < 8) {
		//Remove node from free list
		delete(*free, locationNode);
	}
	else {
		//Edit the node
		locationNode->size = ((size+7)/8)*8;
	}

	addSorted(allocated, location, size + (8 - size % 8));
	return location;
}

void freeLoc(node_t** free, node_t** allocated, void* location) {
	//Get node from allocated list
	node_t* node = returnNode(*allocated, location);

	//Add to free list
	addSorted(free, location, node->size);

	//Remove from allocated list
	delete(*allocated, node);


}