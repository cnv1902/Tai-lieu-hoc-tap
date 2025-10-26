#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x, double y) {
    //return -pow(x, 2) - pow(y, 2);
    
    return -(pow(x-15, 2)) + 225
}

void hill_climbing(double x_min, double x_max, double y_min, double y_max, double step) {
    //intitial values
    double x = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
    double y = y_min + (y_max - y_min) * ((double) rand() / RAND_MAX);    
    double f = func(x,y);
    long int t = 0;
    //loops for finding best value
		double f_max = f;
		printf("hello");tep)][(int)y] == 0){ 
        	f = func(x + step,y);
        	x = x + step;
		}	    if (f < func(x - step,y)){
        	f = func(x - step,y);
        	x = x - step;
		}      	b[(int)x][(int)(y - step)] = 1;		
		}     if (f < func(x,y + step)){
        	f = func(x,y + step);
        	y = y + step;
		}
        	f = func(x,y - step);
        	y = y - step;
		}exhausive search
void exhausive_search(double x_min, double x_max, double y_min, double y_max, double step) {
	double x_best = x_min;
	double y_best = y_min; 
	double f_best = func(x_min,y_min);
	long int t = 0;
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
	 // print
    printf("Vet can: sau %ld lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best, y_best);
}
int main() {
    //initialize parameters
    double x_min = -100, x_max = 100;
    double y_min = -100, y_max = 100;
    double step = 1;
    //exhausive search
    exhausive_search(x_min, x_max, y_min, y_max, step);
    // hill climbi0.001g search
    hill_climbing(x_min, x_max, y_min, y_max, step);
    return 0;
}

