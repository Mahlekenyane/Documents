#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


float timediff_msec(struct timeval t0, struct timeval t1){
	return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec)/1000.0f)*1;
}

double curve(double x){
	double yResult = x*(exp(-1.0*x));

	return yResult;
}

double trapezoidal_ser(int divisions, double start, double end){
	double block_size = (end - start)/divisions;
	double area = 0;

	for (int i = 0; i < divisions-1; ++i){
		double x1 = start + (block_size*i);
		double x2 = x1 + block_size;

		double y1 = x1*(exp(-1.0*x1));
		double y2 = x2*(exp(-1.0*x2));
		double tri_Area = 0, sqr_Area = 0;

		if (y1 < y2){
			double height = y2 - y1;
			double width = block_size;
			tri_Area = 0.5 * (width*height);
			sqr_Area = block_size * y1;
		}
		else{
			double height = y1 - y2;
			double width = block_size;
			tri_Area = 0.5 * (width*height);
			sqr_Area = block_size * y2;
		}

		area += (sqr_Area + tri_Area);
	}

	return area;
}

double trapezoidal_par(int divisions, double start, double end, int threads){
	double block_size = (end - start)/divisions;
	double area = 0;

	omp_set_num_threads(threads);

	#pragma omp parallel for reduction(+:area)
	for(int i = 0; i < divisions-1; ++i){

		double x1 = start + (block_size*i);
		double x2 = x1 + block_size;

		double y1 = x1*(exp(-1.0*x1));
		double y2 = x2*(exp(-1.0*x2));
		double tri_Area = 0, sqr_Area = 0;

		if (y1 < y2){
			double height = y2 - y1;
			double width = block_size;
			tri_Area = 0.5 * (width*height);
			sqr_Area = block_size * y1;
		}
		else{
			double height = y1 - y2;
			double width = block_size;
			tri_Area = 0.5 * (width*height);
			sqr_Area = block_size * y2;
		}

		area += (sqr_Area + tri_Area);
	}

	//printf("%d divisions: %f\n", divisions, area);
	return area;
}

void test_area_accuracy(){
	printf("Test Accuracy...\n");
	FILE *myfile;
	double a = 0, b = 20;
	int rows = 3, num_values = 50;
	double thread_results[rows][num_values];//0\num divisions, 1\serial, 2\2T, 3\4T, 4\8T, 5\16

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < num_values; ++j){
			thread_results[i][j] = 0;
		}
	}

	double trap_area;
	double real_area = 0.99999995670;

	myfile = fopen("trapezoidal_accuracy.txt", "w+");
	for (int i = 0; i < num_values; ++i){
		int num_divisions = i;
		thread_results[0][i] = (double)num_divisions;

		trap_area = trapezoidal_ser(num_divisions, a, b);
		thread_results[1][i] += trap_area;
		thread_results[2][i] += real_area;

		printf("NO. Parts %d \t %0.10f \t %0.10f\n", num_divisions, trap_area, real_area);
		fprintf(myfile, "%d %0.10f %0.10f\n", num_divisions, trap_area, real_area);
	}

	fclose(myfile);
	return;
}

int main(){
	test_area_accuracy();
	printf("Test Parallelization...\n");
	FILE *lab3_1_points;
	double a = 0, b = 20;
	int rows = 6, num_values = 50;
	double thread_results[rows][num_values];//0\num divisions, 1\serial, 2\2T, 3\4T, 4\8T, 5\16

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < num_values; ++j){
			thread_results[i][j] = 0;
		}
	}

	float diff;
	struct timeval start;
	struct timeval end;

	double trap_area;
	int avg = 150;

	for(int j = 0; j < avg; j++){
		printf("Test %d.\n", j);
		for (int i = 1; i < num_values; i++){
			int num_divisions = i*2000;
			thread_results[0][i] = (double)num_divisions;

			gettimeofday(&start, 0);
			trap_area = trapezoidal_ser(num_divisions, a, b);
			gettimeofday(&end, 0);
			diff = timediff_msec(start, end);
			thread_results[1][i] += diff;


			gettimeofday(&start, 0);
			trap_area = trapezoidal_par(num_divisions, a, b, 2);
			gettimeofday(&end, 0);
			diff = timediff_msec(start, end);
			thread_results[2][i] += diff;

			gettimeofday(&start, 0);
			trap_area = trapezoidal_par(num_divisions, a, b, 4);
			gettimeofday(&end, 0);
			diff = timediff_msec(start, end);
			thread_results[3][i] += diff;

			gettimeofday(&start, 0);
			trap_area = trapezoidal_par(num_divisions, a, b, 8);
			gettimeofday(&end, 0);
			diff = timediff_msec(start, end);
			thread_results[4][i] += diff;

			gettimeofday(&start, 0);
			trap_area = trapezoidal_par(num_divisions, a, b, 16);
			gettimeofday(&end, 0);
			diff = timediff_msec(start, end);
			thread_results[5][i] += diff;

		}
	}

	lab3_1_points = fopen("lab3_time_res.txt", "w+");
	for (int i = 0; i < num_values; ++i){
		printf("%f Divs \t ser %f \t 2T %f \t 4T %f \t 8T %f \t 16T %f\n", thread_results[0][i], thread_results[1][i]/avg, thread_results[2][i]/avg, thread_results[3][i]/avg, thread_results[4][i]/avg, thread_results[5][i]/avg);
		fprintf(lab3_1_points, "%f %f %f %f %f %f\n", thread_results[0][i], thread_results[1][i]/avg, thread_results[2][i]/avg, thread_results[3][i]/avg, thread_results[4][i]/avg, thread_results[5][i]/avg);
	}
	fclose(lab3_1_points);
	return 0;
}