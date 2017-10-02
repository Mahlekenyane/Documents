#include "stdio.h"
#include "omp.h"
#include <iostream>

int main() {
	#pragma omp parallel
	{
		int threadId = omp_get_thread_num();
		printf("hello (%d) ", threadId);
		printf("world (%d)\n", threadId); 
	}
	return 0;
}
