#include "stdio.h"
#include "omp.h"
#include <iostream>

int main() {
	#pragma omp parallel
	{
		int threadId = omp_get_thread_num();
		printf("thread (%d) task 1", threadId);
		printf("thread (%d) task 2\n", threadId); 
	}
	return 0;
}
