#include <fstream>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "omp.h"
using namespace std;

double fun (double x) {
	return x * exp(-1.0*x);
}

int main () {
	int noInS = 2000; //no.PointsInSquare
	int noUnC = 0; //no.UnderCurve
	double A = 20.0;
	double B = 0.5;
	for(int i=0; i<=noInS; i++) {
		double x = rand(0.0, A);
		double y = rand(0.0, B);
		if(fun(x) <= y)
			nUnC++;
	}
	double area = A*B*(double)noUnC/(double)noInS;
	cout << area << endl;
	return 0;
}
