#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "omp.h"
using namespace std;

int main () {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;

	float data[8][5]; // x sa 2a 4a 8a
	int maxInS = 80000000;
	int count = 0;
	for(int max=10000000; max<=maxInS; max+=10000000) { //no.PointsInSquare
		double width = 20.0/(double)max;
		//////////////////////////// serial ////////////////////////
		auto t0 = Time::now();
		double area = 0.0;
		for(int i=0; i<max; i++) {
			double a = width*(double)i;
			double b = a + width;
			double trap = 0.5*(a * exp(-1.0*a) + b * exp(-1.0*b))*width;
			area += trap;
		}
		auto t1 = Time::now();
		printf("Serial: = %0.10f\n", area);

		/////////////////////////// 2 threads //////////////////////
		auto t2 = Time::now();
		double area2 = 0.0;
		#pragma omp parallel num_threads(16) shared(width, max)
		{
			#pragma omp for reduction(+:area2)
			for(int i=0; i<=max; i++) {
				double a = width*(double)i;
				double b = a + width;
				double trap = 0.5*(a * exp(-1.0*a) + b * exp(-1.0*b))*width;
				area2 += trap;
			}
		}
		auto t3 = Time::now();
		printf("2 threads: = %0.10f\n", area2);

		/////////////////////////// 4 threads //////////////////////
		auto t4 = Time::now();
		double area4 = 0.0;
		#pragma omp parallel num_threads(4) shared(width, max)
		{
			#pragma omp for reduction(+:area4)
			for(int i=0; i<=max; i++) {
				double a = width*(double)i;
				double b = a + width;
				double trap = 0.5*(a * exp(-1.0*a) + b * exp(-1.0*b))*width;
				area4 += trap;
			}
		}
		auto t5 = Time::now();
		printf("4 threads: = %0.10f\n", area4);

		/////////////////////////// 8 threads //////////////////////
		auto t6 = Time::now();
		double area8 = 0.0;
		#pragma omp parallel num_threads(8) shared(width, max)
		{
			#pragma omp for reduction(+:area8)
			for(int i=0; i<=max; i++) {
				double a = width*(double)i;
				double b = a + width;
				double trap = 0.5*(a * exp(-1.0*a) + b * exp(-1.0*b))*width;
				area8 += trap;
			}
		}
		auto t7 = Time::now();
		printf("8 threads: = %0.10f\n", area8);
		////////////////////////////////////////////////////////

		data[count][0] = (float)max;

		fsec fs1 = t1 - t0;
		data[count][1] = fs1.count();

		fsec fs2 = t3 - t2;
		data[count][2] = fs2.count();

		fsec fs3 = t5 - t4;
		data[count][3] = fs3.count();

		fsec fs4 = t7 - t6;
		data[count][4] = fs4.count();
		count++;
	}

	ofstream myFile;
	myFile.open("lab1.dat");
	for(int i=0; i<8; i++) {
		for(int j=0; j<5; j++)
			myFile << ""+to_string(data[i][j])+" ";
		myFile << "\n";
	}
	myFile.close();
	cout << "number of cores: " << omp_get_num_procs() << endl;
	return 0;
}
