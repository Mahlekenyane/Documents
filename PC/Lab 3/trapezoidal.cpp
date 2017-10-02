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
	double area = 0.0;
	for(int i=0; i<=2000; i++) {
		double a = (double)i/100.0;
		double b = a + 0.01;
		double trap = 0.5*(fun(a)+fun(b))*0.01;
		area += trap;
	}
	cout << area << endl;
	return 0;
}
