/*
Basic Linked List Implementation in C
*/
# include <stdio.h>
# include <stdbool.h>
#include <time.h>
#include <stdlib.h>

//Node Structure
typedef struct node {
	int value;
	struct node* next;
} node_t;

//Function Declarations
void addFirst(node_t** head, int nextval);
void removeFirst(node_t** head);
void addLast(node_t** head, int nextval);
void removeLast(node_t* head);
void sort(node_t* head);
void print(node_t* head);
void freeAll(node_t** head);
bool findMatch(node_t* head, int value);

int main() {
	//Allocate memory for the head node and set it up
	node_t* head = NULL;

	//Intialize randomizer
	srand(time(NULL));

	int i;
	for (i = 0; i < 10; i++) {
		addLast(&head, rand() % 20);
	}

	print(head);
	printf("\n");

	sort(&head);

	print(head);

	return 0;
}

//Add new node to beginning
void addFirst(node_t** head, int nextval) {
	//Allocate memory for new node and set it up
	node_t* next = (node_t*)malloc(sizeof(node_t));
	next->value = nextval;
	next->next = *head; //Set the next to point to the current head
	
	//Set the new node to be the new head
	*head = next;
}

//Remove first item in list
void removeFirst(node_t** head) {
	//Save head.next
	node_t* temp = (*head)->next;
	free(*head);

	//Set the new head to what head originally pointed to
	*head = temp;
}

//Add a new node to end
void addLast(node_t** head, int nextval) {
	//Allocate memory for new node and set it up
	node_t* next = (node_t*)malloc(sizeof(node_t));
	next->value = nextval;
	next->next = NULL;

	if (*head == NULL) {
		*head = next;
		return;
	}
	  
	node_t* temp = *head;

	//Traverse linked list until reaching the end
	while (temp->next != NULL) {
		temp = temp->next;
	}

	//Set next variable in the previous last node to the new last node
	temp->next = next;
}

//Remove the last node
void removeLast(node_t* head) {
	//Allocate memory for temp node and set it up
	node_t* last = (node_t*)malloc(sizeof(node_t));

	if (head == NULL) {
		return;
	}

	//Traverse linked list until reaching the end
	while (head->next != NULL) {
		last = head;
		head = head->next;
	}

	//Release the last node and set the second to last node's next to null
	free(head);
	last->next = NULL;
}

//Free all the nodes
void freeAll(node_t** head) {
	//Traverse list and free everything
	while ((*head)->next != NULL) {
		node_t* temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	//Free last node
	free(*head);
	*head = NULL;
	
}

void sort(node_t** head) {
	//Index starts as first node and is compared to all successive nodes through current
	node_t* index = *head;
	node_t* current = NULL;

	node_t* previndex = NULL;

	//Repeat until index is last node
	while (index->next != NULL) {
		//Set current to node after index
		current = index->next;
		node_t* prevcurrent = index;

		//Repeat for all the remaining nodes
		while (current != NULL) {
			//If index is greater than current, swap them
			if (index->value > current->value) {
				//Handle special case where they are adjacent
				if (index->next == current) {
					node_t* temp = index;
					index = current;
					current = temp;
					current->next = index->next;
					index->next = current;

					//If the node behind index is not null, set its next to index
					if (previndex != NULL) {
						previndex->next = index;
					}
					else {
						//Index is head
						*head = index;
					}
				}
				else {
					node_t* temp = index->next;
					node_t* temp2 = current->next;
					node_t* temp3 = index;

					index = current;
					index->next = temp;
					current = temp3;
					current->next = temp2;

					//Set the next of the node behind current to the new current
					prevcurrent->next = current;

					//If the node behind index is not null, set its next to index
					if (previndex != NULL) {
						previndex->next = index;
					}
					else {
						//Index is head
						*head = index;
					}
				}
				
			}
			prevcurrent = current;
			current = current->next;
		}
		previndex = index;
		index = index->next;
	}
}	

//Return true if the node exists
bool findMatch(node_t* head, int value) {
	//Traverse list and check for match
	while (head->next != NULL) {
		if (head->value == value) {
			return true;
		}
		head = head->next;
	}
	if (head->value == value) {
		return true;
	}
	return false;
}

//Print out the entire linked list
void print(node_t* head) {
	//Traverse list and print out each value
	if (head == NULL) {
		printf("Empty List");
		return;
	}

	while (head->next != NULL) {
		printf("Current node %d", head->value);
		printf("\n");
		head = head->next;
	}
	printf("Last node %d", head->value);
	printf("\n");
}