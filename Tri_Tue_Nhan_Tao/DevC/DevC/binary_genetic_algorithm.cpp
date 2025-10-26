#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POP_SIZE 10  // k�ch thu?c qu?n th?
#define NUM_GENES 5    // d? d�i chu?i gen
#define MUT_RATE 0.01  // t? l? d?t bi?n

// h�m t�nh gi� tr? f(x)
float f(int x) {
    return (-x*x/10.0 + 3.0*x);
}

// h�m t�nh gi� tr? fitness c?a m?t c� th?
float fitness(int* genes) {	
	int x = 0;
	for (int i = 0; i < NUM_GENES; i++) {    
        x += genes[i] * pow(2,NUM_GENES - i - 1);
    }
    return f(x);
}

// h�m ch?n l?c c� th? d? lai gh�p
int select_parent(int** population) {
    float sum_fitness = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        sum_fitness += fitness(population[i]);
    }
    //int r = rand() % sum_fitness;
    float r = ((double) rand() / RAND_MAX) * sum_fitness;    
    int i = 0;
    float partial_sum = 0;
    while (partial_sum < r) {
        partial_sum += fitness(population[i]);
        i++;
    }
    return i-1;
}

// h�m lai gh�p hai c� th?
void crossover(int* parent1, int* parent2, int* child) {
    int crossover_point = rand() % NUM_GENES;
   	for (int i = 0; i < crossover_point; i++)
        child[i] = parent1[i];
	
	for (int i = crossover_point; i < NUM_GENES; i++)
		child[i] = parent2[i];
}

// h�m d?t bi?n m?t c� th?
void mutate(int* genes) {
	for (int i = 0; i < NUM_GENES; i++) {
		if ((double)rand() / RAND_MAX < MUT_RATE) {
			genes[i] = 1 - genes[i];
		}
	}
}

// h�m t?o ra qu?n th? ban d?u
void create_population(int** population) {
	printf("First generation:\n");
	for (int i = 0; i < POP_SIZE; i++) {
		population[i] = (int*)malloc(NUM_GENES * sizeof(int));
		for (int j = 0; j < NUM_GENES; j++) {
			population[i][j] = rand() % 2;
			//
			printf("%d",population[i][j]);
		}
		printf(" = %.2f\n",fitness(population[i]));
	}
}

// h�m t�nh gi� tr? l?n nh?t c?a h�m s? f(x) trong qu?n th? hi?n t?i
float max_fitness(int** population) {
	float max_fit = fitness(population[0]);
	int   k = 0;
	for (int i = 1; i < POP_SIZE; i++) {
		float fit = fitness(population[i]);
		if (fit > max_fit){
			max_fit = fit;
			k = i;
		}
	}
	printf("\nLast generation\n");
	for (int i = 0; i <POP_SIZE; i++ ){
		for (int j = 0; j<NUM_GENES; j++)
			printf("%d",population[i][j]);
		printf(" = %.2f\n",fitness(population[i]));
	}
	printf("\n Max gen = %d :",k);
	return max_fit;
}

// h�m t�m ki?m gi?i ph�p t?t nh?t
void search(int** population) {
	int generation = 1;
	while (generation < 1000) { // gi?i h?n s? th? h?
		int** new_population = (int**)malloc(POP_SIZE * sizeof(int*));
		for (int i = 0; i < POP_SIZE; i++) {
			new_population[i] = (int*)malloc(NUM_GENES * sizeof(int));
			int parent1 = select_parent(population);
			int parent2 = select_parent(population);
			crossover(population[parent1],population[parent2],new_population[i]);
			mutate(new_population[i]);
		}
		for (int i = 0; i < POP_SIZE; i++) {
			free(population[i]);
		}
		free(population);
		population = new_population;
		generation++;
	}
	printf("\n Solution found in generation %d is %f",generation, max_fitness(population));
}

int main() {
	srand(time(NULL));
	int** population = (int**)malloc(POP_SIZE * sizeof(int*));
	create_population(population);
	search(population);
	return 0;
}

