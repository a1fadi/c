
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int furthestReachable(Graph g, int src) {
	int *edges = calloc(GraphNumVertices(g), sizeof(int));
	bool visited[GraphNumVertices(g)];
	for (int i = 0; i < GraphNumVertices(g); i++) {
		visited[i] = false;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		int vert = QueueDequeue(q);
		if (visited[vert] == true) {
			continue;
		}
		visited[vert] = true;
		for (int i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, vert, i) == true &&
			visited[i] == false && i != vert) {
				QueueEnqueue(q, i);
				if (edges[i] == 0) {
					edges[i] = 1 + edges[vert];
				}
			}
		}
	}

	int furthest = 0;
	int index = 0;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (edges[i] >= furthest) {
			furthest = edges[i];
			index = i;
		}
	}

	QueueFree(q);
	free(edges);
	if (furthest == 0) {
		return src;
	}
	return index;
}

