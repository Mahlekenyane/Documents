#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "omp.h"
using namespace std;

int main () {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	float data[20][19]; // x y-ave y-min y-max
	for(int i=0; i<20; i++) {
		for(int j=0; j<19; j++)
			data[i][j]=0;
	}
	for(int i_2=0; i_2<100 ;i_2++) {
		for(int i_1=500000; i_1<=10000000; i_1+=500000) {
			int *a = new int[i_1];
			int *b = new int[i_1];
			for(int i=0; i<i_1; i++) {
				a[i] = 1;
				b[i] = 1;
			}
			int c1 = 0;
			//////////////////// serial ////////////////////
			auto t0 = Time::now();
			for(int i=0; i<i_1; i++) {
				c1+=a[i]*b[i];
			}
			auto t1 = Time::now();
			/////////////// 2 threads //////////////////////
			int c2 = 0;
			auto t2 = Time::now();
			#pragma omp parallel num_threads(2)
			{
				#pragma omp for reduction(+:c2)
				for(int i=0; i<i_1; i++) {
					int tid = omp_get_thread_num();
					c2+=a[i]*b[i];
				}
			}
			auto t3 = Time::now();
			/////////////// 4 threads //////////////////////
			int c3 = 0;
			auto t4 = Time::now();
			#pragma omp parallel num_threads(4)
			{
				#pragma omp for reduction(+:c3)
				for(int i=0; i<i_1; i++) {
					int tid = omp_get_thread_num();
					c3+=a[i]*b[i];
				}
			}
			auto t5 = Time::now();
			/////////////// 8 threads //////////////////////
			int c4 = 0;
			auto t6 = Time::now();
			#pragma omp parallel num_threads(8)
			{
				#pragma omp for reduction(+:c4)
				for(int i=0; i<i_1; i++) {
					int tid = omp_get_thread_num();
					c4+=a[i]*b[i];
				}
			}
			auto t7 = Time::now();
			/////////////// 16 threads /////////////////////
			int c5 = 0;
			auto t8 = Time::now();
			#pragma omp parallel num_threads(16)
			{
				#pragma omp for reduction(+:c5)
				for(int i=0; i<i_1; i++) {
					int tid = omp_get_thread_num();
					c5+=a[i]*b[i];
				}
			}
			auto t9 = Time::now();
			/////////////// 32 threads /////////////////////
			int c6 = 0;
			auto t10 = Time::now();
			#pragma omp parallel num_threads(32)
			{
				#pragma omp for reduction(+:c6)
				for(int i=0; i<i_1; i++) {
					int tid = omp_get_thread_num();
					c6+=a[i]*b[i];
				}
			}
			auto t11 = Time::now();
			////////////////////////////////////////////////
			cout<<"serial: "<<c1+10000000<<"\t 2 threads: "<<c2+10000000<<"\t 4 threads: "<<c3+10000000<<"\t 8 threads: "<<c4+10000000<<"\t 16 threads: "<<c5+10000000<<"\t 32 threads: "<<c6+10000000<<endl;
			fsec fs1 = t1 - t0;
			data[(i_1/500000)-1][0] = 100.0f*(float)i_1;
			data[(i_1/500000)-1][1] += fs1.count();
			if(data[(i_1/500000)-1][2]==0)
				data[(i_1/500000)-1][2] = 100.0f*fs1.count();
			data[(i_1/500000)-1][2] = min(100.0f*fs1.count(), data[(i_1/500000)-1][2]);
			data[(i_1/500000)-1][3] = max(100.0f*fs1.count(), data[(i_1/500000)-1][3]);

			fsec fs2 = t3 - t2;
			data[(i_1/500000)-1][4] += fs2.count();
			if(data[(i_1/500000)-1][5]==0)
				data[(i_1/500000)-1][5] = 100.0f*fs2.count();
			data[(i_1/500000)-1][5] = min(100.0f*fs2.count(), data[(i_1/500000)-1][5]);
			data[(i_1/500000)-1][6] = max(100.0f*fs2.count(), data[(i_1/500000)-1][6]);

			fsec fs3 = t5 - t4;
			data[(i_1/500000)-1][7] += fs3.count();
			if(data[(i_1/500000)-1][8]==0)
				data[(i_1/500000)-1][8] = 100.0f*fs3.count();
			data[(i_1/500000)-1][8] = min(100.0f*fs3.count(), data[(i_1/500000)-1][8]);
			data[(i_1/500000)-1][9] = max(100.0f*fs3.count(), data[(i_1/500000)-1][9]);

			fsec fs4 = t7 - t6;
			data[(i_1/500000)-1][10] += fs4.count();
			if(data[(i_1/500000)-1][11]==0)
				data[(i_1/500000)-1][11] = 100.0f*fs4.count();
			data[(i_1/500000)-1][11] = min(100.0f*fs4.count(), data[(i_1/500000)-1][11]);
			data[(i_1/500000)-1][12] = max(100.0f*fs4.count(), data[(i_1/500000)-1][12]);

			fsec fs5 = t9 - t8;
			data[(i_1/500000)-1][13] += fs5.count();
			if(data[(i_1/500000)-1][14]==0)
				data[(i_1/500000)-1][14] = 100.0f*fs5.count();
			data[(i_1/500000)-1][14] = min(100.0f*fs5.count(), data[(i_1/500000)-1][14]);
			data[(i_1/500000)-1][15] = max(100.0f*fs5.count(), data[(i_1/500000)-1][15]);

			fsec fs6 = t11 - t10;
			data[(i_1/500000)-1][16] += fs6.count();
			if(data[(i_1/500000)-1][17]==0)
				data[(i_1/500000)-1][17] = 100.0f*fs6.count();
			data[(i_1/500000)-1][17] = min(100.0f*fs6.count(), data[(i_1/500000)-1][17]);
			data[(i_1/500000)-1][18] = max(100.0f*fs6.count(), data[(i_1/500000)-1][18]);

			delete[]a;
			delete[]b;
		}
	}

	ofstream myFile;
	myFile.open("lab1.dat");
	for(int i=0; i<20; i++) {
		for(int j=0; j<19; j++)
			myFile << ""+to_string(data[i][j]/100.0f)+" ";
		myFile << "\n";
	}
	myFile.close();
	cout << "number of cores: " << omp_get_num_procs() << endl;
	return 0;
}
