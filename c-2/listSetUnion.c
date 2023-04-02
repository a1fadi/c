
#include "list.h"

int checker(Node s1, int values);
List listSetUnion(List s1, List s2) {
	List uni = malloc(sizeof(*uni));
	uni->head = NULL;

	Node first = s1->head; 
	Node ufirst = uni->head;

	while (first != NULL) {
		Node a = malloc(sizeof(*a));
		a->value = first->value;
		a->next = NULL;


		if (ufirst == NULL) {
			ufirst = a; 
			uni->head = ufirst;
		}

		else {
			int result = 0;
			Node d = uni->head; 
			while (d != NULL) {
				if (d->value == first->value) {
					result = 1;
					break;
				}
				d = d->next;
			}

			if (result == 0) {
				while (ufirst->next != NULL) {
					ufirst = ufirst->next; 
				}
				ufirst->next = a;
			}
			else {
				free(a);
			}
		}

		first = first->next;
	}

	Node second = s2->head; 
	ufirst = uni->head; 

	while (second != NULL) {
		Node a = malloc(sizeof(*a));
		a->value = second->value;
		a->next = NULL;

		if (ufirst == NULL) {
			ufirst = a;
			uni->head = ufirst; 
		}

		else {
			int result = 0;
			Node b = uni->head; 
			while (b != NULL) {
				if (b->value == second->value) {
					result = 1;
				}
				b = b->next;
			}

			if (result == 0) {
				while (ufirst->next!= NULL) {
					ufirst = ufirst->next; 
				}
				ufirst->next = a;
			}
			else {
				free(a);
			}
		}
		 second = second->next;
	}
	return uni;
}


