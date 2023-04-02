
#include "list.h"

bool listIsPalindromic(List l) {
	Node last = l->last; 
	Node first = l->first; 
	while (1) {
		if (first == last) {
			break;
		}
		
		if (last->value != first->value) {
			return false;
		}
		first = first->next; 
		if (first == last) {
			break;
		}
		last = last->prev;
	}
	return true;
}

