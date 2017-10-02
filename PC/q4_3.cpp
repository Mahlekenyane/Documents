#include "stdio.h"
#include <math.h>
#include "omp.h"
#include <iostream>
using namespace std;

int main() {
	// program to sum some stuff
	int f = 1;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:f)
		for(int i=1; i<=4; i++) {
			for(int j=0; j<1; j++) { // 1st thread does least work, last thread does most
				f += (j+1);
			}
		}
	}
	cout << f << endl;
	//solution to load imbalance may require moving parallel loop

	// program to sum some stuff
	f = 1;
	#pragma omp parallel num_threads(4)
	{
		for(int i=1; i<=4; i++) {
			#pragma omp for reduction(+:f)
			for(int j=0; j<1; j++) { // 1st thread does least work, last thread does most
				f += (j+1);
			}
		}
	}
	cout << f << endl;
	return 0;
}
