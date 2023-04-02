
#include "list.h"

void reverseDLList(List l) {
	Node curr = l->first;
	Node prev = NULL;
	while(curr != NULL) {	
		Node temp = curr; 
		curr = curr->next; 
		temp->next = prev; 
		temp->prev = prev->prev;
		prev = temp;
	}
}

