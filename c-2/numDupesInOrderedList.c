
#include "list.h"

int numDupesInOrderedList(List l) {
	Node verifier;
	verifier = malloc(sizeof(Node));
	int duplicate_counter = 0;
	if (l->head == NULL || l->head->next == NULL) {
		return duplicate_counter;
	}
	verifier = l->head;
	
	int difference;
	while (verifier->next != NULL) {
		difference = (verifier->value) - (verifier->next->value);
		if (difference == 0) {
			duplicate_counter++;
		}
		verifier = verifier->next;
	}
	return duplicate_counter;
}

