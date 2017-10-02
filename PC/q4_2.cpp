#include "stdio.h"
#include "omp.h"
#include <iostream>
using namespace std;

int main() {
	int sum = 0;
	#pragma omp parallel num_threads(10)
	{
		#pragma omp for reduction(+:sum)
		for(int i=0; i<10; i++) {
			sum += i;
		}
	}
	cout << sum << endl;
	return 0;
}
