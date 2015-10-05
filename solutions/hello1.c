
#include <stdio.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main (int argc, char * argv[])

{

    int rank = 0, size = 1;
    double a, b;

#ifdef _OPENMP
#pragma omp parallel private(rank, size)
#endif
    {
#ifdef _OPENMP
	rank = omp_get_thread_num();
	size = omp_get_num_threads();
#endif

	{
	  if (rank == 0)
	  {
	    a = sqrt(2.0);
	    b = 0;
	    printf( "Hello from processor %d of %d, a=%g, b=%g\n", rank, size, a, b );
	  }
	  if (rank == 1)
	  {
	    a = 0;
	    b = sqrt(3.0);
	    printf( "Hello from processor %d of %d, a=%g, b=%g\n", rank, size, a, b );
	  }
	}
    }
    return 0;
}
