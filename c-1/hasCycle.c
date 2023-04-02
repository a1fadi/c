
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

bool hasCycle(Graph g) {
	if (GraphNumVertices(g) == 0) {
		return false;
	}
	
    Stack s = StackNew();
    int *visited = calloc(GraphNumVertices(g), sizeof(int));
	int *parent = calloc(GraphNumVertices(g), sizeof(int));
	
    StackPush(s, 0);
    // Conduct the dfs 
    while (!StackIsEmpty(s)) {
        int city = StackPop(s);
        if (visited[city] == 1) {
            continue;
        }
        visited[city] = 1;
		for (int i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, i, city)) {
				if (visited[i] == 1) {
					for (int x = 0; x < GraphNumVertices(g); x++) {
						if (x != i && x != city) {
							for (int b = 0; b < GraphNumVertices(g); b++) {
								if (parent[b] = p)
							}
							}
						}
					}
				}
				parent[i] = city;
				StackPush(s, i);
				}
			}

    }
    // Free everything accordingly
    StackDrop(s);
    free(visited);
	return false;
}

