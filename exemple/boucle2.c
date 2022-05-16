#include <stdio.h>
#include <omp.h>

int main(void) {
   float A[10000];
   float sum = 0.;
   int i;
#pragma omp parallel
  {
	
#pragma omp for
    for(i=1;i<10000;i++){
        A[i] = 1./i/i;
    }
  }
  for(i=1;i<10000;i++){
     sum += A[i];
  }
  printf("La somme est %f\n", sum);
}

