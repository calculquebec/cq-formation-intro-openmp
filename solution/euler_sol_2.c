#include <stdio.h>
#include <omp.h>
#define N 100

int main(void) {
  int i;
  double fact[N], sum=0.;

  fact[0]=1;
  for(i=1;i<N;i++){
    fact[i] = i*fact[i-1];
  }
#pragma omp parallel for reduction(+:sum)
  for(i=0;i<N;i++){
    sum += 1./fact[i];
  }
  printf("The sum is %f\n",sum);
}
