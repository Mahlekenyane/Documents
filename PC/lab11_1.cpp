#include <fstream>
#include <chrono>
#include <iostream>
using namespace std;

int main () {
	auto start = now();
	for(int i_1=10; i_1<10000; i_1+=10) {
		int **arr = new int*[i_1];
		for(int i=0; i<i_1; i++)
			arr[i] = new int[i_1];
	}
	auto finish = now();
	ofstream myFile;
	myFile.open("lab1.dat");
	myFile.close();
}
