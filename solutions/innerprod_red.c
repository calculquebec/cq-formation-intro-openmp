/* innerprod.c */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main(void)
{
    int *a, *b, ip, i;
    double t1, t2;

    a = malloc(N * sizeof(*a));
    b = malloc(N * sizeof(*b));

    for (i = 0; i < N; i++) {
        a[i] = 2;
        b[i] = 3;
    }

    t1 = omp_get_wtime();
    ip = 0;

#pragma omp parallel for private(i) shared (a,b) reduction(+:ip)
      for (i = 0; i < N; i++)
        ip += a[i] * b[i];

    t2 = omp_get_wtime();

    printf("Inner product = %d, time=%g\n", ip, t2-t1);
    return 0;
}
