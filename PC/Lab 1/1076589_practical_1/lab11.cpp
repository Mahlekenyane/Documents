#include <fstream>
#include <chrono>
#include <iostream>
using namespace std;

int main () { 
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	float rowMajor[20][2];
	float colMajor[20][2];
	for(int i=0; i<20; i++) {
		rowMajor[i][0] = 0;
		colMajor[i][0] = 0;
	}
	for(int i_2=0; i_2<10 ;i_2++) {
		for(int i_1=100; i_1<2100; i_1+=100) {
			int **arr = new int*[i_1];
			for(int i=0; i<i_1; i++)
				arr[i] = new int[i_1];
		
			auto t0 = Time::now();
			for(int i=0; i<i_1; i++) {
				for(int j=0; j<i_1; j++)
					arr[i][j]=5;
			}
			auto t1 = Time::now();
			fsec fs = t1 - t0;
			rowMajor[(i_1/100)-1][0] += fs.count();
			rowMajor[(i_1/100)-1][1] = (float)i_1;
		
			auto t3 = Time::now();
			for(int i=0; i<i_1; i++) {
				for(int j=0; j<i_1; j++) {
					arr[j][i]=5;
				}
			}
			auto t4 = Time::now();
			fsec fs1 = t4 - t3;
			colMajor[(i_1/100)-1][0] += fs1.count();
			colMajor[(i_1/100)-1][1] = (float)i_1;
		
			//cout<<fs.count()<<"\n";
			//cout<<fs1.count()<<"\n";
			delete[]arr;
		}
	}

	ofstream myFile;
	myFile.open("lab1.dat");/*
	myFile << "0 0 1\n";*/
	myFile << "#arr. size row Maj. col Maj.\n";
	for(int i=0; i<20; i++) {
		myFile << ""+to_string(rowMajor[i][1])+" "+to_string(rowMajor[i][0]/10.0)+" "+to_string(colMajor[i][0]/10.0)+"\n";
	}/*
	myFile << "\n";
	for(int i=0; i<20; i++) {
		myFile << ""+to_string(colMajor[i][1])+" "+to_string(colMajor[i][0])+" 0.8\n";
	}*/
	myFile.close();
	return 0;
}
