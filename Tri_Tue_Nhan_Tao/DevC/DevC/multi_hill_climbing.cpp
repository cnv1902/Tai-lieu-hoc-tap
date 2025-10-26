#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14

double func(double x, double y) {
   return - (sqrt((x-50)*(x-50) +4*(y-150)*(y-150))+20*cos(2*PI*x/30)+20*cos(2*PI*y/40));
}

void multi_start_hill_climbing(double x_min, double x_max, double y_min, double y_max, double step, int num_starts) {
    //initialize the best values
    double f_best = -INFINITY;
    double x_best, y_best;
    int t = 0;
    //iteration num_starts hill-climbing
    for (int i = 0; i < num_starts; i++) {
        //initialize for each hill-climbing       
        double x = x_min + (x_max - x_min) * ((double) rand() / RAND_MAX);
        double y = y_min + (y_max - y_min) * ((double) rand() / RAND_MAX);
        double f = func(x,y);
        
         //loops for finding best value
	    while (true) {
			double f_max = f; 
	        if (f < func(x + step,y)){
	        	f = func(x + step,y);
	        	x = x + step;
			}
	        if (f < func(x - step,y)){
	        	f = func(x - step,y);
	        	x = x - step;
			}		
	        if (f < func(x,y + step)){
	        	f = func(x,y + step);
	        	y = y + step;
			}
	        if (f < func(x,y - step)){
	        	f = func(x,y - step);
	        	y = y - step;
			}
	        if (f == f_max){
	        	break;
			}
			t++;
	    }    		
        //keep the best values
        if (f > f_best) {
            f_best = f;
            x_best = x;
            y_best = y;
        }
    }
    // print results
    printf("Leo doi: Sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best, y_best);
}

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
	 // print results
    printf("Vet can: sau %d lap, gia tri lon nhat la %f tai diem (%f, %f)\n", t, f_best, x_best, y_best);
}

int main() {
	// initialize parameter values
	double x_min = 0.0, x_max = 100.0;
    double y_min = 100, y_max = 200.0;
	double step = 0.005;
	
	//exhausive search
    exhausive_search(x_min, x_max, y_min, y_max, step);
    
	// number of hill-climbing algorithm
	int num_starts = 50;	
	multi_start_hill_climbing(x_min, x_max, y_min, y_max, step, num_starts);
	
	return 0;
}
