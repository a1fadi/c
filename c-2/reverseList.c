
#include "list.h"

void listReverse(List l) {

	if (l->head == NULL || l->head->next == NULL) {
		return;
	}

	Node verifier;
	verifier = malloc(sizeof(Node));
	verifier = l->head;

	Node counter;
	counter = malloc(sizeof(Node));
	counter = l->head;

	List duplicate; 
	duplicate = malloc(sizeof(List));
	
	// Check length of list 
	int length = 0; 
	while (verifier != NULL) {
		length++;
		verifier = verifier->next;
	}
	// Go through the list and change the value of original list 

	while (length > 0) {
		counter = l->head;
		int count = 1;
		while (count < length) {
			counter = counter->next; 
			count++;
		}
		if (duplicate->head == NULL) {
			duplicate->head = counter; 
			duplicate->head->next = NULL;
		}
		else {
			Node catcher;
			catcher = malloc(sizeof(Node));
			catcher = l->head;
			while(catcher->next != NULL) {
				catcher = catcher->next;
			}
			catcher->next = counter; 
			catcher->next->next = NULL;
		}
		length--;
	}

	verifier = l->head; 
	counter = l->head;
	while (verifier->next != NULL) {
		verifier = verifier->next; 
		free(counter);
		counter = verifier; 
		if (verifier->next == NULL) {
			free(verifier);
		}
	}

	l->head = duplicate->head;

	}


