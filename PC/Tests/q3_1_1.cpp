#include "stdio.h"
#include <math.h>
#include <iostream>
using namespace std;

int main() {
	int a = 5;
	int b = 50;
	int max = 10000000;
	double h = 45.0/(double)max;
	double integral = 0.0;
	for(int i=1; i<=max; i++) {
		integral += h*exp(-1.0*(a + h*i));
	}
	cout << integral << endl;
	return 0;
}
