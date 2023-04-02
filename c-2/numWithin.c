
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	Queue q = QueueNew();
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	int *edges = malloc(GraphNumVertices(g) * sizeof(int));

	for (int i = 0; i < GraphNumVertices(g); i++) {
		edges[i] = 100000;
	}
	edges[src] = 0;

	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		int road = QueueDequeue(q);
		if (visited[road] == 1) {
			continue;
		}
		visited[road] = 1;
		for (int i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, road, i) && i != road && visited[i] == 0 && edges[i] > edges[road]) {
				edges[i] = edges[road] + 1;
				QueueEnqueue(q, i);
			}
		}
	}
	free(visited);
	
	QueueFree(q);

	int i = 0; 
	for (int x = 0; x < GraphNumVertices(g); x++) {
		if (edges[x] <= dist) {
			i++;
		}
	}
	free(edges);
	return i;
}

