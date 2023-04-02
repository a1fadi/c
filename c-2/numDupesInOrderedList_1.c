
#include "list.h"

int numDupesInOrderedList(List l) {
	int dupes;
	if (l->head == NULL) {
		dupes = 0;
	}
	else if (l->head->next == NULL) {
		dupes = 0;
	}
	else {
		Node loop = l->head;
		dupes = 0;
		int value = loop->value;
		loop = loop->next;

		while (loop != NULL) {
			if (loop->value == value) {
				dupes++;
			}
			value = loop->value;
			loop = loop->next;
		}
	}
	return dupes;
}

