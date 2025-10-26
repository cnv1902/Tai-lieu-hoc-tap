#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITER 100000
#define INITIAL_TEMP 1000.0
#define COOLING_FACTOR 0.98
#define MIN_TEMP 1e-5
#define NUM_NEIGHBORS 10
#define PROB 0.01

double func(double x)
{
    //return -x * x/10 + 3*x;  //[0, 31]
    return sin(x)+x*cos(x); //[-20,30]
}

void simulated_annealing(double x_min, double x_max){
    double x = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
    double f = func(x);
    
    double T = INITIAL_TEMP;
    double x_best = x;
    double f_best = f;
    int t = 1;
    while (T > MIN_TEMP && t < MAX_ITER) {
        for (int i = 0; i < NUM_NEIGHBORS; i++) {
            double x_new = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
            double f_new = func(x_new);
            double delta = f_new - f;
            if (delta > 0 || exp(delta / T) > PROB) {
                x = x_new;
                f = f_new;
            }
            if (f_best< f_new) {
                x_best = x_new;
                f_best = f_new;
            }
        }
        T *= COOLING_FACTOR;
        t++;
    }
    printf("Simulated Annealing: Sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best);	
}
//vet can
void exhausive_search(double x_min, double x_max, double step){
	double x_best = x_min;
	double f_best = func(x_min);
	int t = 0;
	for (double x = x_min; x <= x_max; x = x + step){
		double f = func(x);
		if (f_best < f){
			x_best = x;
			f_best = f;
		 } 
		t++;
	}
	printf("Vet can: Sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best);	
}
int main()
{
    srand(time(NULL));
    double x_min = -20;
    double x_max = 30.0;
    double step = 0.0001;
    exhausive_search(x_min,x_max,step);
    simulated_annealing(x_min,x_max);
    return 0;
}

