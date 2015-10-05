/* innerprod.c */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main(void)
{
    int *a, *b, ip, i, *localips, tid, localip;
    double t1, t2;

    a = malloc(N * sizeof(*a));
    b = malloc(N * sizeof(*b));
    localips = malloc(omp_get_max_threads()*sizeof(*localips));

    for (i = 0; i < N; i++) {
        a[i] = 2;
        b[i] = 3;
    }

    t1 = omp_get_wtime();
    ip = 0;

#pragma omp parallel private(i,tid,localip) shared (ip,a,b,localips)
    {
      tid = omp_get_thread_num();
      localip = 0;
#pragma omp for nowait
      for (i = 0; i < N; i++)
        localip += a[i] * b[i];
      localips[tid] = localip;
#pragma omp barrier
#pragma omp single
      for (i = 0; i < omp_get_num_threads(); i++)
	ip += localips[i];
    }

    t2 = omp_get_wtime();

    printf("Inner product = %d, time=%g\n", ip, t2-t1);
    return 0;
}
