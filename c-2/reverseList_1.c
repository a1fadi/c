
#include "list.h"

Node reverser(Node l, int size);
Node traverser(Node l, int size);
void listReverse(List l) {
	Node point = NULL; 
	Node first = l->head;
	while (first != NULL) {
		Node temp = first; 
		first = first->next;
		temp->next = point; 
		point = temp;
	} 
	l->head = point;
}
