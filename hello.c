
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main (int argc, char * argv[])

{

    int rank = 0, size = 1;

#ifdef _OPENMP
#pragma omp parallel private(rank, size)
#endif
    {
#ifdef _OPENMP
	rank = omp_get_thread_num();
	size = omp_get_num_threads();
#endif

        printf( "Hello from processor %d of %d\n", rank, size );
    }
    return 0;
}
