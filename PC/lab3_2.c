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

double get_max_height(int start, int end, int numPoints){
	double max = 0.0, temp = 0.0;
	double step = ((double)(end-start))/numPoints;

	for (int i = 0; i < numPoints; ++i){
		temp = curve(start + (step*i));
		if (temp > max){
			max = temp;
		}
	}

	return max;
}

double monte_carlo_ser(int start, int end, int numPoints, double max_height){
	double div_x = RAND_MAX/(end-start);
	double div_y = RAND_MAX/max_height;

	double box_area = (end-start)*max_height;
	int num_points_under = 0;

	for (int i = 0; i < numPoints; ++i){

		double x = (rand()/div_x)+start;
		double y = (rand()/div_y);
		
		double curve_y = x*(exp(-1.0*x));
		if (y <= curve_y){
			num_points_under++;
		}
	}


	double area = (double)((double)num_points_under/(double)numPoints)*box_area;
	return area;
}

double monte_carlo_par(int start, int end, int numPoints, double max_height, int numThreads){
	double div_x = RAND_MAX/(end-start);
	double div_y = RAND_MAX/max_height;

	double box_area = (end-start)*max_height;
	int num_points_under = 0;

		double x;
		double y;
		double curve_y;

	omp_set_num_threads(numThreads);
	#pragma omp parallel for reduction(+:num_points_under)
	for (int i = 0; i < numPoints; ++i){
		x = (rand()/div_x)+start;
		y = (rand()/div_y);
		curve_y = x*(exp(-1.0*x));
		if (y <= curve_y){
			num_points_under++;
		}
	}

	double area = (double)((double)num_points_under/(double)numPoints)*box_area;
	//printf("par area accuracy %d = %0.10f\n", numPoints, (area-0.99999995670));
	return area;
}

int main(){
	FILE *lab3_2_points, *lab3_2_errors_up, *lab3_2_errors_down;
	srand(time(NULL));

	int rows = 6, num_values = 100;
	double thread_results[num_values][rows];//0\num divisions, 1\serial, 2\2T, 3\4T, 4\8T, 5\16
	//double thread_error_up[rows][num_values];
	//double thread_error_down[rows][num_values];

	for (int i = 0; i < num_values; ++i){
		for (int j = 0; j < rows; ++j){
			thread_results[i][j] = 0;
			//thread_error_up[i][j] = 0;
			//thread_error_down[i][j] = 10000;
		}
	}

	float diff;
	struct timeval start_time;
	struct timeval end_time; 


	int start = 0, end = 20;
	int num_points = 20;
	double real_area = 0.99999995670;
	double max_height = get_max_height(start, end, num_points);
	int avg = 10;
	//double test = monte_carlo_ser(start, end, 1000, max_height);
	//printf("test = %0.10f\n", test);
	double area;
	for (int i = 0; i < num_values; ++i){
		int size = i*1000;
		thread_results[i][0] = size;
		printf("%d points:\n", size);

		for(int j = 0; j < avg; j++){

			//2T
			gettimeofday(&start_time, 0);
			area = monte_carlo_par(start, end, size, max_height, 2);
			gettimeofday(&end_time, 0);
			diff = timediff_msec(start_time, end_time);
			thread_results[i][2] += diff;

			printf("2T %0.10f \t", diff);

			//4T
			gettimeofday(&start_time, 0);
			area = monte_carlo_par(start, end, size, max_height, 4);
			gettimeofday(&end_time, 0);
			diff = timediff_msec(start_time, end_time);
			thread_results[i][3] += diff;

			printf("4T %0.10f \t", diff);

			//8T
			gettimeofday(&start_time, 0);
			area = monte_carlo_par(start, end, size, max_height, 8);
			gettimeofday(&end_time, 0);
			diff = timediff_msec(start_time, end_time);
			thread_results[i][4] += diff;

			printf("8T %0.10f \t", diff);

			//16T
			gettimeofday(&start_time, 0);
			area = monte_carlo_par(start, end, size, max_height, 16);
			gettimeofday(&end_time, 0);
			diff = timediff_msec(start_time, end_time);
			thread_results[i][5] += diff;

			printf("16T %0.10f", diff);

			//ser
			gettimeofday(&start_time, 0);
			area = monte_carlo_ser(start, end, size, max_height);
			gettimeofday(&end_time, 0);
			diff = timediff_msec(start_time, end_time);
			thread_results[i][1] += diff;

			printf("Ser %0.10f\n", diff);
		}
		printf("\n");
		thread_results[i][1] = thread_results[i][1]/avg;
		thread_results[i][2] = thread_results[i][2]/avg;
		thread_results[i][3] = thread_results[i][3]/avg;
		thread_results[i][4] = thread_results[i][4]/avg;
		thread_results[i][5] = thread_results[i][5]/avg;
	}


	lab3_2_points = fopen("lab3_2_time_res.txt", "w+");
	//lab3_2_errors_up = fopen("lab3_2_error_up_res.txt", "w+");
	//lab3_2_errors_down = fopen("lab3_2_error_down_res.txt", "w+");

	for (int i = 0; i < num_values; ++i){
		int k = i;
		printf("%f points \t ser %0.11f \t 2T %0.11f \t 4T %0.11f \t 8T %0.11f \t 16T %0.11f\n", thread_results[i][0], thread_results[i][1], thread_results[i][2], thread_results[i][3], thread_results[i][4], thread_results[i][5]);
		fprintf(lab3_2_points, "%f %0.11f %0.11f %0.11f %0.11f %0.11f\n", thread_results[i][0], thread_results[i][1], thread_results[i][2], thread_results[i][3], thread_results[i][4], thread_results[i][5]);
	}

	fclose(lab3_2_points);
	//fclose(lab3_2_errors_up);
	//fclose(lab3_2_errors_down);
	return 0;
}