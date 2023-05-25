#include <stdio.h>

int fib(int n){
  int i, j, out;
  if (n<2)
    return n;
  else
    {
       #pragma omp task firstprivate(n) shared(i)
       i=fib(n-1);

       #pragma omp task firstprivate(n) shared(j)
       j=fib(n-2);

       #pragma omp taskwait
       return i + j;
    }
}

int main()
{
  int n = 20;

  #pragma omp parallel shared(n)
  {
    #pragma omp single
    printf ("fib(%d) = %d\n", n, fib(n));
  }
}
