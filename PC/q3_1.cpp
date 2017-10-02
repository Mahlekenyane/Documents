#include "stdio.h"
#include "omp.h"
#include <iostream>
using namespace std;

int main() {
	int sum = 0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum)
		for(int i=0; i<i_1; i++) {
			c2+=a[i]*b[i];
		}
	}
	cout << sum << endl;
	return 0;
}
