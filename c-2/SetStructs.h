// COMP2521 22T2 Assignment 1

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct node {
	int item;           // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *left;  // DO NOT CHANGE/REMOVE THIS FIELD
	struct node *right; // DO NOT CHANGE/REMOVE THIS FIELD
	int next_biggest;
	
	// You may add more fields here if needed
};

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct set {
	struct node *tree;  // DO NOT CHANGE/REMOVE THIS FIELD
	int node_counter;

	// You may add more fields here if needed
};

// You may define more structs here if needed 

////////////////////////////////////////////////////////////////////////
// Cursors

struct cursor {
	struct set *set; // You may add more fields here if needed
	int current_item; 
	int counter; 
};

////////////////////////////////////////////////////////////////////////

