
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
#include <limits.h>

struct graph {
	int nV;
	bool **edges;
};

int shortestDistance(Graph g, int src, int dest) {
    int num_cities = GraphNumVertices(g);
    int edges[num_cities];
	bool visited[num_cities];

    for (int i = 0; i < num_cities; i++) {
        edges[i] = INT_MAX;
		visited[i] = false;
    }    
    edges[src] = 0;
	

    for (int i = 0; i < num_cities - 1; i++) {
        int min_index = num_cities + 1; 
        int min_edges = INT_MAX;
        
        // Finds the city with the smallest distance that hasnt been visited
        // so that we can explore its roads next
        for (int a = 0; a < num_cities; a++) {
            if (visited[a] == false && edges[a] <= min_edges) {
                min_index = a;
                min_edges = edges[a];
            } 
        }

        // smallest unvisited city now marked as visited
        visited[min_index] = true;

        for (int a = 0; a < num_cities; a++) {
			if (GraphIsAdjacent(g, a, min_index) == true) {
				int edgy = edges[min_index] + 1;
         	   // if the city we are looking at hasnt been visited 
				if (visited[a] == false) {
					// if we have found a shorter route for a city store it
					if (edges[min_index] != INT_MAX && edgy < edges[a]) {
						// update distances, turns, parents and stamina arrays
						// for the respective destination cities
						edges[a] = edgy;
					}
				}   
			}
		}
	}
	if (edges[dest] == INT_MAX) {
		return -1;
	}
	return edges[dest];
}

