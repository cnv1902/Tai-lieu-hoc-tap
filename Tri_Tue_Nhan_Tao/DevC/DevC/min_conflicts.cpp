#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define NUM_VERTICES 1100
#define NUM_COLORS 200
#define MAX_STEPs 90000

// function to implement the min-conflicts algorithm for map coloring
bool min_conflicts(char graph[][NUM_VERTICES], int colors[]) {    
    //initialize a complete assignment
    for (int i = 0; i < NUM_VERTICES; i++) {
        colors[i] = rand() % NUM_COLORS;
    }
	//loop for finding a solution
    for (int t = 1; t<= MAX_STEPs; t++) {
    	// find a set of conflicted variables
    	int X[NUM_VERTICES], k = 0; 
    	for (int i = 0; i < NUM_VERTICES; i++) { 
		    for (int j = 0; j < NUM_VERTICES; j++) {
		        if (graph[i][j] == 1 && colors[i] == colors[j]) {
		          	X[k] = i;
		          	k++;
		        }
		    }
		}			
		// check a solution	
        if (k == 0){		
			return true;        
        }        
        // select a random vertex
        int r = rand() % k; 
        int i = X[r];
        int color = colors[i];        
        // count the number of conflicts for the current color assignment
        int numConflicts = 0;
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (i != j && graph[i][j] == 1 && colors[i] == colors[j]) {
                numConflicts++;
            }
        }
        // select the color that minimizes conflicts
        int minConflicts = numConflicts;
        for (int c = 0; c < NUM_COLORS; c++) {
            if (c != colors[i]) {
                int conflicts = 0;
                for (int j = 0; j < NUM_VERTICES; j++) {
                    if (i != j && graph[i][j] == 1 && c == colors[j]) {
                        conflicts++;
                    }
                }
                if (conflicts < minConflicts) {
                    minConflicts = conflicts;
                    color = c;
                }
            }
        }
        // assign the color to the vertex i
        colors[i] = color;        
    }
    return false;
}

int main() {
	srand(time(0));
    //example adjacency matrix representing a graph with 5 vertices and 5 colors
    /*
	char graph[NUM_VERTICES][NUM_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };
    */
    // create a random graph
    char  graph[NUM_VERTICES][NUM_VERTICES];
    for (int i = 0; i<NUM_VERTICES; i++){
    	for (int j = 0; j<=i; j++){
    		graph[i][j] = rand() % 2;    		
    		graph[j][i] = graph[i][j];
    		graph[i][i] = 0;    		
		}
	}
	/*
	//print	
	 for (int i = 0; i<NUM_VERTICES; i++){
    	for (int j = 0; j<NUM_VERTICES; j++){
    		printf("%5d",graph[i][j]);
    	}
    	printf("\n");
    }
    */
	// initialize colors array
    int colors[NUM_COLORS];
    // run the min-conflicts algorithm
    bool found = min_conflicts(graph, colors);
    if (found) {
     	for (int i = 0; i < NUM_VERTICES; i++) {
        	printf("\n Vertex %d <-- color %d", i, colors[i]);
        	Sleep(1);
    	}
	} 
	else {
		printf("\n There exists no solution.\n");
	}
return 0;
}

