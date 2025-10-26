#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define NUM_VERTICES 5
#define MAX_COLORS 3

bool consistent(int i, int c, char graph[][NUM_VERTICES], int colors[]) {
    for (int j = 0; j < NUM_VERTICES; j++) {
        if (graph[i][j] ==1 && colors[j] == c) {
            return false;
        }
    }
    return true;
}

bool backtrack(int i, char graph[][NUM_VERTICES], int colors[]) {
    if (i == NUM_VERTICES) {
        return true; // all nodes are colored
    }
    for (int c = 1; c <= MAX_COLORS; c++) {
        if (consistent(i, c, graph, colors)) {
            colors[i] = c;
            if (backtrack(i + 1, graph, colors)) {
                return true; // found a valid color assignment
            }
            colors[i] = -1; // reset color if no valid color assignment found
        }
    }
    return false; // no valid color assignment found
}

int main() {
	//srand(time(0));
 	//example adjacency matrix representing a graph with 5 vertices and 5 colors
    char graph[NUM_VERTICES][NUM_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };  
    /*
     // create a random graph
    char graph[NUM_VERTICES][NUM_VERTICES];
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
	// array to store the colors for each node                             
    int colors[NUM_VERTICES]; 
    // initialize colors to -1 (no color assigned)
    for (int i = 0; i < NUM_VERTICES; i++) {
        colors[i] = -1; 
    }

    if (backtrack(0, graph, colors)) {
        for (int i = 0; i < NUM_VERTICES; i++) {
            printf("Vertex %d <-- color %d\n", i, colors[i]);
            Sleep(1);
        }
    } 
	else {
        printf("\n There exists no solution.\n");
    }
    return 0;
}

