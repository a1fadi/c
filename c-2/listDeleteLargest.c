
#include "list.h"
#include "assert.h"

int listDeleteLargest(List l) {
	assert(l != NULL);

	int biggest;
	if (l->head->next == NULL) {
		biggest = l->head->value;
		l->head = NULL;
		return biggest;
	}

	Node w = l->head; 
	biggest = w->value;
	while (w != NULL) {
		if (w->value > biggest) {
			biggest = w->value;
		}
		w = w->next;
	}

	w = l->head->next; 
	Node before = l->head;
	if (before->value == biggest) {
		l->head = w;
		free(before);
		return biggest;
	}
	while (w->value != biggest) {
		w = w->next; 
		before = before->next;
	}

	before->next = w->next;

	free(w); 
	return biggest;
}

