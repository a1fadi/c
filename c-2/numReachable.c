
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int resulter(Graph g, bool *visited, int src);
int numReachable(Graph g, int src) {
	int num_cities = GraphNumVertices(g);
	bool *visited = malloc(num_cities*sizeof(bool));
	for (int i = 0; i < num_cities; i++) {
		visited[i] = false;
	} 
	int result = resulter(g, visited, src);
	return result;	
}

int resulter(Graph g, bool *visited, int src) {
	visited[src] = true;
	int result = 1;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (GraphIsAdjacent(g, src, i) == true && visited[i] == false) {
			result += resulter(g, visited, i);
		}
	}
	return result;
}

