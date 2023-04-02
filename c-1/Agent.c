// COMP2521 Ass2 - Police academy
// Agent data structure implementation
//
// Authors:
// Fadi Al Hatu z5309136
// Written: 5/08/2022 

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "Agent.h"
#include "Map.h"
#include "Stack.h"


// This struct stores information about an individual agent and can be
// used to store information that the agent needs to remember.
struct agent {
    char *name; 
    int startLocation;
    int location; // stores current location of agent
    int maxStamina; // max stamina
    int stamina; // current stamina
    Road *roads;
    Road *legalRoads;
    int strategy; // stores game strategy agent is using
    int *visited; //array of cities visited
    int turn; // stores what turn they are on (used for strat 2)
    int informed; // used if an agent has seen an informant
    int *shortestPath; // used to store an agents shortest path 
    int shortestPathSteps; // used to store the length of shortest path
    int *roadMatrix; // used for dfs strategy 
    Map map;
};

// stack struct for stage 2 
struct stack {
    int index;
    int size;
    int *array;
};


static Move chooseRandomMove(Agent agent, Map m);
static Move cheapestLeastVisited(Agent agent, Map m);
static Move dfsMove(Agent agent, Map m);
int *dfsCalculator(Agent agent, Map m);
static int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]);
int *shortestPath(Agent agent, int location);

/**
 * Creates a new agent
 */

Agent AgentNew(int start, int stamina, int strategy, Map m, char *name) {
    if (start >= MapNumCities(m)) {
        fprintf(stderr, "error: starting city (%d) is invalid\n", start);
        exit(EXIT_FAILURE);
    }

    Agent agent = malloc(sizeof(struct agent));
    if (agent == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
        
    agent->startLocation = start;
    agent->location = start;
    agent->maxStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = m;
    agent->name = strdup(name);
    agent->turn = 0;
    agent->informed = 0;
    // Initialise roads and legal road arrays for agents on strategy 1
    // To store all the roads they could go on each turn 
    agent->roads = malloc(MapNumCities(m) * sizeof(Road));
    if (agent->roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    agent->legalRoads = malloc(MapNumCities(m) * sizeof(Road));
    if (agent->legalRoads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    agent->shortestPath = NULL;
    agent->shortestPathSteps = 0;
    // Used for stage 2, initialised by calculating path using stack 
    // at run time(start)
    agent->roadMatrix = dfsCalculator(agent, m);

    // Initialise the agent visited array for stage 1
    agent->visited = (int*)calloc(MapNumCities(m), sizeof(int));
    if (agent->visited == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Initialise the agents starting location to be visited once 
    agent->visited[agent->startLocation]++;
    return agent;
}

/**
 * Frees all memory associated with the agent
 * NOTE: You should not free the map because the map is owned by the
 *       main program, and the main program will free it
 */
void AgentFree(Agent agent) {
    free(agent->shortestPath);
    free(agent->roadMatrix);
    free(agent->roads);
    free(agent->legalRoads);
    free(agent->visited);
    free(agent->name);
    free(agent);
}

////////////////////////////////////////////////////////////////////////
// Making moves

/**
 * Calculates the agent's next move
 */
Move AgentGetNextMove(Agent agent, Map m) {
    switch (agent->strategy) {
        case STATIONARY:             return (Move){agent->location, 0};
        case RANDOM:                 return chooseRandomMove(agent, m);
        case CHEAPEST_LEAST_VISITED: return cheapestLeastVisited(agent, m);
        case DFS:                    return dfsMove(agent, m);
        default:
            printf("error: strategy not implemented yet\n");
            exit(EXIT_FAILURE);
    }
}

static Move chooseRandomMove(Agent agent, Map m) {
    // If the agent has been informed then take shortest path 
    if (agent->informed == 1 && agent->turn < agent->shortestPathSteps) {
        Move move;    
        // Destination is equal to the agents individual path and the turn 
        // that they are on
        int destination = agent->shortestPath[agent->turn];
        // Call MapContainsRoad to find length of road from agents location
        // to the destination 
        int length = MapContainsRoad(m, agent->location, destination);
        // If the length is more than the agents stamina, agent rests.
        if (length > agent->stamina) {
            move = (Move){agent->location, 0};
        } else {
            move = (Move){destination, length};
            agent->turn++;
        }
        return move;
    }
    // Initalise two 'Road' arrays to store all roads and legal roads
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));
    if (legalRoads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

    // Initialise the roads
    Move move;
    // Provided there are legal roads
    if (numLegalRoads > 0) {
        // Sort the roads using insertion sort
        for (int i = 1; i < numLegalRoads; i++) {
            Road r = legalRoads[i];
            int j = i;
            while (j > 0 && r.to < legalRoads[j - 1].to) {
                legalRoads[j] = legalRoads[j - 1];
                j--;
            }
            legalRoads[j] = r;
        }
        
        // nextMove is randomly chosen from the legal roads
        int k = rand() % numLegalRoads;
        move = (Move){legalRoads[k].to, legalRoads[k].length};
    } else {
        // The agent must stay in the same location
        move = (Move){agent->location, 0};
    }
    
    free(legalRoads);
    free(roads);
    return move;
}
// Used for stage 1, finds Least visited/Closest city to vist and returns move
static Move cheapestLeastVisited(Agent agent, Map m) {
    //If there has been an informant 
    if (agent->informed == 1 && agent->turn < agent->shortestPathSteps) {
        Move move;    
        // Destination is equal to the agents individual path and the turn 
        // that they are on
        int destination = agent->shortestPath[agent->turn];
        // Call MapContainsRoad to find length of road from agents location
        // to the destination 
        int length = MapContainsRoad(m, agent->location, destination);
        // If the length is more than the agents stamina, agent rests.
        if (length > agent->stamina) {
            move = (Move){agent->location, 0};
            agent->visited[agent->location]++;
        }
        else {
            move = (Move){destination, length};
            agent->visited[destination]++;
            agent->turn++;
        }
        return move;
    }

    // set agents roads and legal to new variables for simplicity
    Road *roads = agent->roads; 
    Road *legalRoads = agent->legalRoads; 

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    Move move;
    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);
    // If there are no roads the agent can go to, stay where you are
    if (numLegalRoads == 0) {
        move = (Move){agent->location, 0};
        // Increment the visited array for that location
        agent->visited[agent->location]++;
        return move;
    } 

    // If there is only one legal road, then the agent has to go to that road
    else if (numLegalRoads == 1) {
        // return move accordingly and increase the visited array 
        move = (Move){legalRoads[0].to, legalRoads[0].length};
        agent->visited[legalRoads[0].to]++;
        return move;
    } 
    
    else {
        // Find cities that have been visited the least
        int min_index = INT_MAX;
        // Find the road destination with lowest index and store it
        for (int i = 0; i < numLegalRoads; i++) {
            if (agent->visited[legalRoads[i].to] < min_index) {
                min_index = agent->visited[legalRoads[i].to];
            }
        }
        
        // Initialise array for roads that have been visited equally least 
        // amount of times
        Road *leastRoads = malloc(MapNumCities(m) * sizeof(Road));
        if (leastRoads == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }

        // Find all the roads that have been visited equally least times 
        int numLeastRoads = 0;
        for (int i = 0; i < numLegalRoads; i++) {
            if (agent->visited[legalRoads[i].to] == min_index) {
                leastRoads[numLeastRoads++] = legalRoads[i];
            }
        }

        // In the case where there are more than 1 road that has been visited the least 
        // Find the road that requires the least amount of stamina 
        int index = INT_MAX;
        Road Chosen; 
        // We need to insure that the agent has enough stamina for the 
        // shortest road 
        int StaminaReq = agent->stamina;
        for (int i = 0; i < numLeastRoads; i++) {
            // If the road is shorter or equal (because we can still travel 
            // on roads equal to our stamina than any previous roads
            if (leastRoads[i].length <= StaminaReq) {
                // If the road is equal to previous road and the city index is higher 
                // then skip to the next value as we need to ensure the lowest shortest 
                // road is used 
                if (leastRoads[i].length == StaminaReq && i >= index) {
                    continue;
                }
                // Otherwise update the required values
                else {
                    StaminaReq = leastRoads[i].length; 
                    Chosen = leastRoads[i];
                    index = i;
                }
            }
        }
        // Return the move accordingly 
        move = (Move){Chosen.to, Chosen.length};
        agent->visited[Chosen.to]++;

        free(leastRoads);
        return move;
    }
}

// Used for stage 2, returns agents next move 
static Move dfsMove(Agent agent, Map m) {

    //If there has been an informant 
    if (agent->informed == 1 && agent->turn < agent->shortestPathSteps) {
        Move move;    
        // Destination is equal to the agents individual path and the turn 
        // that they are on
        int destination = agent->shortestPath[agent->turn];
        // Call MapContainsRoad to find length of road from agents location
        // to the destination 
        int length = MapContainsRoad(m, agent->location, destination);

        // If the length is more than the agents stamina, agent rests.
        if (length > agent->stamina) {
            move = (Move){agent->location, 0};
        }
        else {
            move = (Move){destination, length};
            agent->turn++;
        }
        return move;
    }
    // If the agents turn has outlasted the length of their path, we need 
    // to reset their strategy 
    if (agent->turn > agent->shortestPathSteps && agent->informed == 1) {
        // Reset their turn count to 0 to allow a proper path
        agent->turn = 0;
        // They are no longer informed 
        agent->informed = 0;
        // Calculate their path using the dfs
        agent->roadMatrix = dfsCalculator(agent, m);
    }

    // if agent has gone to the end of their stack 
    if (agent->turn >= MapNumCities(m)) {
        // Reset their turn to 0
        agent->turn = 0;
        // Recalculate their matrix from their current location
        agent->roadMatrix = dfsCalculator(agent, m);
    }

    // Check to see if their is sufficient stamina for the move
    Move move;    
    // Destination is equal to the agents individual path and the turn 
    // that they are on
    int destination = agent->roadMatrix[agent->turn + 1];
    // Call MapContainsRoad to find length of road from agents location
    // to the destination 
    int length = MapContainsRoad(m, agent->location, destination);
    // If the length is more than the agents stamina, agent rests.
    if (length > agent->stamina) {
        move = (Move){agent->location, 0};
        return move;
    }
    // Else set the move accordingly and increment the turn variable
    move = (Move){destination, length};
    agent->turn++;
    return move;
}

// Used for stage 2, uses DFS to calculate path for agent to use
// Returns said path array 
int *dfsCalculator(Agent agent, Map m) {
    // Sets up stack 
    Stack s = StackNew((MapNumCities(m) *3));
    // Sets up visited, predecessor and path arrays
    // Stores if a city has been visited or not
    int *visited = calloc(MapNumCities(m), sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Stores the predecessors of each city for backtracking 
    int *predecessor = calloc(MapNumCities(m), sizeof(int));
    if (predecessor == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Stores the path to return to the agent 
    int path_count = 0;
    int *path = calloc(MapNumCities(m) * 3, sizeof(int));
    if (path == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Push first city onto stack  
    StackPush(s, agent->location);
    // Check if a predecssor value is passed and hence 
    // push a visited city 
    int backtracker = 0;
    // Conduct the dfs 
    while (!StackIsEmpty(s)) {
        // Take first city off the stack 
        int city = StackPop(s);
        // If city has been visited and not backtracking
        // move to next value
        if (visited[city] == 1 && backtracker == 0) {
            continue;
        }
        // Reset backtracker if its being used
        if (backtracker == 1) {
            backtracker = 0;
        }
        // Mark city as visited
        visited[city] = 1;

        // Add city to the path 
        path[path_count] = city; 
        path_count++;
        // Create array roads from city to see valid roads 
        Road *roads = malloc(MapNumCities(m) * sizeof(Road));
        if (roads == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        // Count how many roads there are from each city
        int numRoads = MapGetRoadsFrom(m, city, roads);

        // Count how many valid (non visited roads) road
        int valid_roads = 0;
        for (int i = numRoads -1; i >= 0; i--) {
            // If a road hasnt been visited, push it and set the predecessor 
            if (visited[roads[i].to] == 0) {
                StackPush(s, roads[i].to);
                predecessor[roads[i].to] = city;
                valid_roads++;
            }
        }

        // If no unvisited roads exist, return back to before 
        // as long as we havent visited every city yet (as this 
        // will cause an infinite stack)
        if (valid_roads == 0) {
            // We need to see if we have visited every city yet 
            int total_cities = 0;
            for (int i = 0; i < MapNumCities(m); i++) {
                if (visited[i] == 1) {
                    total_cities++;
                }
            }
            // If we havent seen every city yet push the predecssor 
            // onto the stack 
            if (total_cities < MapNumCities(m)) {
                StackPush(s, predecessor[city]);
                backtracker = 1;
            }
        }
        free(roads);
    }
    // Free everything accordingly
    StackFree(s);
    free(visited);
    free(predecessor);
    // return the path for the agent 
    return path;
}

// Used to find roads that agent has enough stamina for 
static int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]) {
    int numLegalRoads = 0;
    for (int i = 0; i < numRoads; i++) {
        if (roads[i].length <= agent->stamina) {
            legalRoads[numLegalRoads++] = roads[i];
        }
    }
    return numLegalRoads;
}

/**
 * Executes a given move by updating the agent's internal state
 */
void AgentMakeNextMove(Agent agent, Move move) {
    if (move.to == agent->location) {
        agent->stamina = agent->maxStamina;
    } else {
        agent->stamina -= move.staminaCost;
    }
    agent->location = move.to;
}

////////////////////////////////////////////////////////////////////////
// Gets information about the agent
// NOTE: It is expected that these functions do not need to be modified

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent) {
    return agent->name;
}

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent) {
    return agent->location;
}

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent) {
    return agent->stamina;
}

////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is, sets the new path 
 // for the agent to follow
 */
void AgentGainInfo(Agent agent, int thiefLocation) {
    // Reset their turn to 0
    agent->turn = 0;
    // Free their existing shortestPath if they had one 
    free(agent->shortestPath);
    // Set new shortest path to equal the function below
    agent->shortestPath = shortestPath(agent, thiefLocation);
    // Display to other functions that agent is on his shortest path
    agent->informed = 1; 
}

// Function to develop shortest path for the agent 
int *shortestPath(Agent agent, int thiefLocation) {
    // Initialise variables regarding maps, number of 
    // cities, a parents, visited, turns and distances 
    // array for implementation of Dijkstras algorithm 
    Map m = agent->map;
    int num_cities = MapNumCities(m);
    int parents[num_cities];
    bool visited[num_cities];
    int turns[num_cities]; 
    int distances[num_cities];
    int staminas[num_cities];

    // initialise the arrays to be equal to infinity
    // visited arrays to equal false and staminas to equal -1
    for (int i = 0; i < num_cities; i++) {
        turns[i] = INT_MAX;
        distances[i] = INT_MAX;
        visited[i] = false;
        staminas[i] = -1;
    }    

    // Set the agents current location to have 
    // no parents/distances and turns taken to reach and current stamina
    turns[agent->location] = 0;
    distances[agent->location] = 0;
    parents[agent->location] = -1;
    staminas[agent->location] = AgentStamina(agent);
    
    // find the shortest distance for all cities 
    for (int i = 0; i < num_cities - 1; i++) {
        int min_index = num_cities + 1; 
        int min_distance = INT_MAX;
        
        // Finds the city with the smallest distance that hasnt been visited
        // so that we can explore its roads next
        for (int a = 0; a < num_cities; a++) {
            if (visited[a] == false && distances[a] <= min_distance) {
                min_index = a;
                min_distance = distances[a];
            } 
        }

        // smallest unvisited city now marked as visited
        visited[min_index] = true; 

        // Find the smallest not seen city that has a road 
        // from the city we are looking at 
        Road *roads = malloc(MapNumCities(m) * sizeof(Road));
        if (roads == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        int num_roads = MapGetRoadsFrom(m, min_index, roads);

        for (int a = 0; a < num_roads; a++) {
            int destination = roads[a].to;
            int length = roads[a].length;
            // Variable to store how many moves the city would take 
            // to reach
            int move_turns;
            // Calculate how much stamina agent would have left after this route
            int stamina = length - staminas[min_index];
            
            // if we have enough stamina to complete the move without a break
            // the road only takes one turn 
            if (stamina >= 0) {
               move_turns = 1;
               
            // if stamina is negative, we need to take a break and hence the 
            // the route would take 2 turns 
            } else {
                move_turns = 2; 
                stamina = agent->maxStamina - length;
            }
            
            // if the city we are looking at hasnt been visited 
            if (visited[destination] == false) {
                // if we have found a shorter route for a city store it
                if (
                    move_turns + turns[min_index] < turns[destination]) {
                        // update distances, turns, parents and stamina arrays
                        // for the respective destination cities
                        distances[destination] = distances[min_index] + length;
                        turns[destination] = move_turns;
                        parents[destination] = min_index;
                        staminas[destination] = stamina;
                }
            }   
        }
        free(roads);
     }

     // Find how many turns it takes to get to the thief location city
     int target = thiefLocation;
     int numTurns = 0;

    // while we havent traced back from the theifs location 
    // to current location keep looping
    while (1) {
        // Target is equal to the predecessor of target
        target = parents[target];
        // If we are in current location, break out the loop
        if (target == -1) {
            break;
        }
        // store how many turns it takes to get there
        numTurns++;
    }
    // Set the agent struct value to equal numTurns
    agent->shortestPathSteps = numTurns;

    // make a shortest path for the agent to have
    // to lead them to the thief
    int *path = calloc(MapNumCities(m), sizeof(int));
    if (path == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    target = thiefLocation;
    // Store all the shortest cities visited from thief location 
    // to our current location in a new path
    for (int i = 0; i < numTurns; i++) {
        path[i] = target;
        target = parents[target];
    }

    // Reverse the array to get correct path  
    int temp;
    int tempEnd = numTurns -1;
    for (int i = 0; i < tempEnd; i++) {
        temp = path[i];  
        path[i] = path[tempEnd];
        path[tempEnd] = temp;
        tempEnd--;
    }
    // return the shortest path back to the agent 
    return path; 
}

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent) {
    //       You can leave this function blank if you want
}