
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfs(Graph g, int *visited, int src);
void depthFirstSearch(Graph g, int src) {
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	dfs(g, visited, src);
	free(visited);
}

void dfs(Graph g, int *visited, int src) {
	printf("%d ", src);
	visited[src] = 1;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (GraphIsAdjacent(g, src, i) && visited[i] == 0) {
			dfs(g,visited, i);
		}
	}
}
