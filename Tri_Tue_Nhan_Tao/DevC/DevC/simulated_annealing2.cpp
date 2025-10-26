#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITER 50000
#define INITIAL_TEMP 1000.0
#define COOLING_FACTOR 0.98
#define MIN_TEMP 1e-5
#define NUM_NEIGHBORS 20
#define PROB 0.01
#define PI 3.14

double func(double x, double y){
    return - (sqrt((x-50)*(x-50) +4*(y-150)*(y-150))+20*cos(2*PI*x/30)+20*cos(2*PI*y/40));
}

void simulated_annealing(double x_min, double y_min, double x_max, double y_max){
    double x = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
    double y = y_min + (y_max - y_min) * ((double) rand() / RAND_MAX);
    double f = func(x,y);
     
    double T = INITIAL_TEMP;
    double x_best = x, y_best = y;
    double f_best = f;
    int t = 1;
    while (T > MIN_TEMP && t < MAX_ITER) {
        for (int i = 0; i < NUM_NEIGHBORS; i++) {
            double x_new = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
            double y_new = y_min + (y_max - y_min) * ((double) rand() / RAND_MAX);
            	
            double f_new = func(x_new,y_new);
            double delta = f_new - f;
            if (delta > 0 || exp(delta / T) > PROB) {
                x = x_new;
                y = y_new;
                f = f_new;
            }
            if (f_best< f_new) {
                x_best = x_new;
                y_best = y_new;
                f_best = f_new;
            }
        }
        T *= COOLING_FACTOR;
        t++;
    }
    printf("Simulated Annealing: Sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best, y_best);	
}
//vet can
void exhausive_search(double x_min, double x_max, double y_min, double y_max, double step) {
	double x_best = x_min;
	double y_best = y_min; 
	double f_best = func(x_min,y_min);
	int t = 0;
	for (double x = x_min; x <= x_max; x = x + step)
		for (double y = y_min; y<= y_max; y = y + step){
			double f = func(x,y);
			if (f_best <f){
				x_best = x;
				y_best = y;
				f_best = f;
			}    
			t++;
		}
	 // In k?t qu?
    printf("Vet can: sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best, y_best);
}

int main(){
    srand(time(NULL));
    double x_min = 0.0, x_max = 100.0;
    double y_min = 100, y_max = 200.0;
    double step = 0.01;
    //vet can
    exhausive_search(x_min, x_max, y_min, y_max, step);
    //Simulated Annealing
    simulated_annealing(x_min,y_min,x_max,y_max);
    return 0;
}

