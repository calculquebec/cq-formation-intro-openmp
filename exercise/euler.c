#include <stdio.h>
#include <omp.h>

int main(void) {
  int i;
  double fact[100], sum=0.;

  fact[0]=1;
  for(i=1;i<100;i++){
    fact[i] = i*fact[i-1];
  }

  for(i=0;i<100;i++){
    sum += 1./fact[i];
  }
  printf("The sum is %f\n",sum);
}
