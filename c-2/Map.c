// COMP2521 Ass2 - Police academy
// Map data structure implementation
//
// Authors:
// Fadi Al Hatu z5309136
// Written: 5/08/2022 


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

// Definition of a city


// Struct containing map of the world, map contains number of 
// vertices, edges and amount where each edge leads to

struct map { 
    int nV;        
    int nE;        
    int **roads;
    char **cities;
};


/**
 * Creates a new map with the given number of cities
 * Assumes that numCities is positive
 */

 
Map MapNew(int numCities) {
    // Malloc m, have an error message in case it doesnt work
    Map m = malloc(sizeof(*m));
    if (m == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Set the amount of verticies to equal the number of cities inputted
    m->nV = numCities;
    // Number of edges is 0 for now
    m->nE = 0;
    
    // Initialise cities array
    m->cities = malloc(numCities * sizeof(char*));
    if (m->cities == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numCities; i++) {
        m->cities[i] = "unnamed";
    }

    // Create the roads adjacency matrix and print error message if doesnt work
    m->roads = malloc(numCities * sizeof(int *));
    if (m->roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Initialises all the values in the roads matrix to be equal to 0
    for (int i = 0; i < numCities; i++) {
        m->roads[i] = calloc(numCities, sizeof(int));
        if (m->roads[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }
    // Return new map
    return m;
}

/**
 * Frees all memory associated with the given map
 */
void MapFree(Map m) {
    for (int i = 0; i < m->nV; i++) {
        free(m->roads[i]);
    }
    for (int i = 0; i < m->nV; i++) {
        free(m->cities[i]);
    }
    free(m->cities);
    free(m->roads);
    free(m);
}

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m) {
    return m->nV;
}

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m) {
    return m->nE;
}

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length) {
    // Sets the road adjacency matrix accordingly, with both 
    // cities having a road of length 'length' to the next city
    if (m->roads[city1][city2] == 0.0) {
        m->roads[city1][city2] = length;
        m->roads[city2][city1] = length;
        m->nE++;
    } 
}

/**
 * Sets the name of the given city
 */
void MapSetName(Map m, int city, char *name) {     
    m->cities[city] = strdup(name);
}

/**
 * Returns the name of the given city
 */
char *MapGetName(Map m, int city) {
    return m->cities[city];
}

/**
 * Checks if there is a road between the two given cities
 * Returns the length of the road if there is a road, and 0 otherwise
 */
int MapContainsRoad(Map m, int city1, int city2) {
    // if the the corresponding position in the adjacecny 
    // matrix is bigger than 0, return 1
    if (m->roads[city1][city2] > 0.0) {
        return m->roads[city1][city2];
    }
    return 0;
}

/**
 * Returns the number of roads connected to the given city and stores
 * them in the given roads array. The `from` field should be equal to
 * `city` for all the roads in the array.
 * Assumes that the roads array is large enough to store all the roads
 */
int MapGetRoadsFrom(Map m, int city, Road roads[]) {
    assert(city >= 0 && city <= m->nV);
    // Variable to store number of roads in each city
    int numRoads = 0;
    // Loops through the road adjacency matrix and adds to numRoads 
    // everytime there is a road, stores the road into roads array
    for (int i = 0; i < m->nV; i++) {
        if (i != city && MapContainsRoad(m, city, i) != 0) {
            Road a;
            a.from = city; 
            a.to = i;
            a.length = m->roads[city][i];
            roads[numRoads] = a;
            numRoads++;
        }
    }
    return numRoads;
}

/**
 * Displays the map
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * This function will work once the other functions are working
 */
void MapShow(Map m) {
    printf("Number of cities: %d\n", MapNumCities(m));
    printf("Number of roads: %d\n", MapNumRoads(m));
    
    Road *roads = malloc(MapNumRoads(m) * sizeof(Road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);    
    }
    
    for (int i = 0; i < MapNumCities(m); i++) {
        printf("[%d] %s has roads to:", i, MapGetName(m, i));
        int numRoads = MapGetRoadsFrom(m, i, roads);
        for (int j = 0; j < numRoads; j++) {
            if (j > 0) {
                printf(",");
            }
            printf(" [%d] %s (%d)", roads[j].to, MapGetName(m, roads[j].to),
                   roads[j].length);
        }
        printf("\n");
    }
    
    free(roads);
}

