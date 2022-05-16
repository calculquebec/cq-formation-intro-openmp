#include <stdio.h>
#include <omp.h>

int main(void) {
int i, N=1000000000;
double pi_i, sum = 0.;
#pragma omp parallel for private(pi_i)
  for(i=0;i<N;i+=2){
    pi_i = 4./(2.*i+1.);
    pi_i -= 4./(2.*i+3.);
#pragma omp atomic
    sum += pi_i;
  }
  printf("pi = %f\n",sum);
}
