#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

struct node *insert_tail(int value, struct node *head);
struct node *strings_to_list(int len, char *strings[]);
void print_list(struct node *head);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    int value;
    scanf("%d", &value);
    // create linked list from command line arguments
    struct node *head = NULL;
    if (argc > 1) {
        // list has elements
        head = strings_to_list(argc - 1, &argv[1]);
    }

    struct node *new_head = insert_tail(value, head);
    print_list(new_head);

    return 0;
}


// Insert a new node containing value at the end of the linked list.
// The head of the new list is returned.
struct node *insert_tail(int value, struct node *head) {

    struct node *new = (struct node*) malloc(sizeof(struct node));
    new->data = value;
    new->next = NULL;
    
    if (head == NULL) {
    
    head = new; 
    }
    
    else { 
        
        struct node *lastnode = head;
        
        while (lastnode->next != NULL) {
            
            lastnode = lastnode -> next;
        }
        
        lastnode->next = new;
    }
    return head;

}


// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
        i -= 1;
    }   
    return head;
}

// DO NOT CHANGE THIS FUNCTION
// print linked list
void print_list(struct node *head) {
    printf("[");    
    struct node *n = head;
    while (n != NULL) {
        // If you're getting an error here,
        // you have returned an invalid list
        printf("%d", n->data);
        if (n->next != NULL) {
            printf(", ");
        }
        n = n->next;
    }
    printf("]\n");
}
