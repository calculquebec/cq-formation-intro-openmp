/* innerprod.c */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000
#define PAD 16

int main(void)
{
    int *a, *b, ip, i, (*localips)[PAD];
    double t1, t2;

    a = malloc(N * sizeof(*a));
    b = malloc(N * sizeof(*b));
    localips = malloc(omp_get_max_threads()*sizeof(*localips));

#pragma omp parallel for default(none) private(i) shared (a,b)
    for (i = 0; i < N; i++) {
        a[i] = 2;
        b[i] = 3;
    }

    t1 = omp_get_wtime();
    ip = 0;

#pragma omp parallel default(none) private(i) shared (ip,a,b,localips)
    {
      int tid = omp_get_thread_num();
      localips[tid][0] = 0;
#pragma omp for
      for (i = 0; i < N; i++)
	localips[tid][0] += a[i] * b[i];
#pragma omp single
      for (i = 0; i < omp_get_num_threads(); i++)
	ip += localips[i][0];
    }

    t2 = omp_get_wtime();

    printf("Inner product = %d, time=%g\n", ip, t2-t1);
    return 0;
}
