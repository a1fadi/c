
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	Queue q = QueueNew();
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		int road = QueueDequeue(q);
		if (visited[road] == 1) {
			continue;
		}
		printf("%d ", road);
		visited[road] = 1;
		for (int i = 0; i < GraphNumVertices(g); i++) {
			if (GraphIsAdjacent(g, road, i) && visited[i] == 0) {
				QueueEnqueue(q, i);
			}
		}
	}
	free(visited);
	QueueFree(q);
}

