#include <omp.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, i;
    double pi;

    do {
        printf("Enter the number of intervals (0 quits) : ");
        fflush(stdout);
        scanf("%d", &n);
        if (n > 0) printf("-> %d iterations\n", n); else printf("done\n");

        if (n == 0) break;

        pi = 0.0;
#pragma omp parallel for private(i) reduction(+:pi)
        for (i = n - 1; i >= 0; i--) {
            pi += (4.0 - ((i & 1) << 3)) / (2.0 * i + 1);
        }

        printf("PI is approximately %.16f, Error is %.16f\n",
            pi, fabs(pi - M_PI));
    } while (1);

    return 0;
}
