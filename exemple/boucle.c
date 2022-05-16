#include <stdio.h>
#include <omp.h>

int main(void) {
   float A[10000];
   float sum = 0.;
#pragma omp parallel
  {
	int i;
    int fil_n = omp_get_thread_num();
    int num_fils = omp_get_num_threads();
    for(i=fil_n+1;i<10000;i+=num_fils){
        A[i] = 1./i/i;
    }
  }
  int i;
  for(i=1;i<10000;i++){
     sum += A[i];
  }
  printf("La somme est %f\n", sum);
}
