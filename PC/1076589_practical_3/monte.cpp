#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <random>
#include "omp.h"
using namespace std;

int main () {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;

	float data[8][5]; // x sa 2a 4a 8a
	random_device rd;
	mt19937 gen(rd());
	int maxInS = 80000000;
	int count = 0;
	for(int noInS=10000000; noInS<=maxInS; noInS+=10000000) { //no.PointsInSquare
		double A = 20.0;
		double B = 0.5;
		uniform_real_distribution<> disx(0.0, A);
		uniform_real_distribution<> disy(0.0, B);

		//////////////////////////// serial ////////////////////////
		auto t0 = Time::now();
		int noUnC = 0; //no.UnderCurve
		for(int i=0; i<=noInS; i++) {
			double x = disx(gen);
			double y = disy(gen);
			if(x * exp(-1.0*x) > y)
				noUnC++;
		}
		double area = A*B*(double)noUnC/(double)noInS;
		auto t1 = Time::now();
		cout << "Serial: " << area << endl;

		/////////////////////////// 2 threads //////////////////////
		auto t2 = Time::now();
		int noUnC2 = 0;
		#pragma omp parallel num_threads(2)
		{
			#pragma omp for reduction(+:noUnC2)
			for(int i=0; i<=noInS; i++) {
				double x = disx(gen);
				double y = disy(gen);
				if(x * exp(-1.0*x) > y)
					noUnC2++;
			}
		}
		double area2 = A*B*(double)noUnC2/(double)noInS;
		auto t3 = Time::now();
		cout << "Thread 2: " << area2 << endl;

		/////////////////////////// 2 threads //////////////////////
		auto t4 = Time::now();
		int noUnC4 = 0;
		#pragma omp parallel num_threads(4)
		{
			#pragma omp for reduction(+:noUnC4)
			for(int i=0; i<=noInS; i++) {
				double x = disx(gen);
				double y = disy(gen);
				if(x * exp(-1.0*x) > y)
					noUnC4++;
			}
		}
		double area4 = A*B*(double)noUnC4/(double)noInS;
		auto t5 = Time::now();
		cout << "Thread 4: " << area4 << endl;

		/////////////////////////// 2 threads //////////////////////
		auto t6 = Time::now();
		int noUnC8 = 0;
		#pragma omp parallel num_threads(8)
		{
			#pragma omp for reduction(+:noUnC8)
			for(int i=0; i<=noInS; i++) {
				double x = disx(gen);
				double y = disy(gen);
				if(x * exp(-1.0*x) > y)
					noUnC8++;
			}
		}
		double area8 = A*B*(double)noUnC8/(double)noInS;
		auto t7 = Time::now();
		cout << "Thread 8: " << area8 << endl;
		////////////////////////////////////////////////////////

		data[count][0] = (float)noInS;

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
	myFile << "0 0 0 0 0\n";
	for(int i=0; i<8; i++) {
		for(int j=0; j<5; j++)
			myFile << ""+to_string(data[i][j])+" ";
		myFile << "\n";
	}
	myFile.close();
	cout << "number of cores: " << omp_get_num_procs() << endl;
	return 0;
}
