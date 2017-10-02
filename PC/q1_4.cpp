#include "stdio.h"
#include "omp.h"
#include <iostream>
using namespace std;

int main() {
	int sum = 0;
	int*arr = new int[4];
	// with race condition
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for(int i=0; i<40; i++) {
			int ind = omp_get_thread_num();
			arr[ind] += i; // threads racing to use shared array
		}
	}
	for (int i=0; i<4; i++)
		sum += arr[i];
	cout << sum << endl;
	
	sum = 0;
	// without race condition
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum)
		for(int i=0; i<40; i++) {
			int ind = omp_get_thread_num() - 1;
			sum += i; // threads have own copy of var, no sharing, no race condition
		}
	}
	cout << sum << endl;
	return 0;
}
