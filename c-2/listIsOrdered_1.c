
#include "list.h"
bool checker(Node l, int direction); 
bool listIsOrdered(List l) {
	if (l->head == NULL) {
		return true;
	}
	else if (l->head->next == NULL) {
		return true;
	}
	else {
		// find out the direction its meant to be going
		Node node = l->head;
		int direction = 0;
		int value;
		Node tester = node;
		value = tester->value;

		while (tester->next != NULL) {
			if (tester->value != value) {
				direction = value - tester->value;
				break;
			}
			tester = tester->next;
		}	
		if (direction == 0) {
			return true;
		}
		return checker(l->head, direction);
	}
	return true;
}

bool checker(Node l, int direction) {
	int head = l->value;
	l = l->next;
	while (l->next != NULL) {
		if (l->value == head) {
			l = l->next;
		}
		else {
			if (direction < 0) {
				if (head - l->value > direction) {
					return false;
				}
			} else {
				if (head - l->value < direction) {
					return false;
				}
			}
			direction = head - l->value;
			l = l->next;
		}
	}
	return true;
}