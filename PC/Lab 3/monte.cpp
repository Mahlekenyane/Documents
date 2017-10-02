#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <random>
#include "omp.h"
using namespace std;

double fun (double x) {
	return x * exp(-1.0*x);
}

int main () {
	random_device rd;
	mt19937 gen(rd());
	int noInS = 20000; //no.PointsInSquare
	int noUnC = 0; //no.UnderCurve
	double A = 20.0;
	double B = 0.5;
	uniform_real_distribution<> disx(0.0, A);
	uniform_real_distribution<> disy(0.0, B);
	for(int i=0; i<=noInS; i++) {
		double x = disx(gen);
		double y = disy(gen);
		if(fun(x) > y)
			noUnC++;
	}
	double area = A*B*(double)noUnC/(double)noInS;
	cout << area << endl;
	return 0;
}
