
#include "list.h"

bool listIsOrdered(List l) {
	Node verifier;
	verifier = malloc(sizeof(Node));
	if (l->head == NULL || l->head->next == NULL) {
		return true;
	}
	verifier = l->head;
	int difference = verifier->value - verifier->next->value; 
	
	while (difference == 0) {
		if (verifier->next == NULL) {
			break;
		}
		difference = verifier->value - verifier->next->value;
		verifier = verifier->next;
	} 

	if (difference > 0) {
		while (verifier->next != NULL) {
			difference = verifier->value - verifier->next->value;
			if (difference < 0) {
				return false;
			}
			verifier = verifier->next;
		}
		return true; 
	}

	else {
		while (verifier->next != NULL) {
			difference = verifier->value - verifier->next->value;
			if (difference > 0) {
				return false;
			}
			verifier = verifier->next;
		}
		return true; 
	}

	
	return false;
}

