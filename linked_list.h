# include <stdbool.h>

//Node Structure
typedef struct node {
	void* ptr;
	unsigned int size;
	struct node* next;
} node_t;

void addFirst(node_t** head, void* nextval);
void addSorted(node_t** head, void* nextval, unsigned int size);
void removeFirst(node_t** head);
void addLast(node_t** head, void* nextval);
void removeLast(node_t* head);
void delete(node_t* head, node_t* node);
node_t* returnNode(node_t* head, void* location);
node_t* smallestLocation(node_t* head, unsigned int size);
void sort(node_t* head);
void print(node_t* head);
void freeAll(node_t** head);
bool findMatch(node_t* head, void* value);