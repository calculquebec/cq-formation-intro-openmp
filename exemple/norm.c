#include <stdio.h>
#include <omp.h>
#include <math.h>
#define N 100

int main(void){
  double vec[N], norm=0., norm2=0.;
  int i;

#pragma omp parallel default(none) shared(vec,norm,norm2) private(i)
{
#pragma omp for 
  for(i=0;i<N;i++){
    vec[i] = i*(1+i*(0.05+i*0.0025));
  }
#pragma omp for reduction(+:norm2) 
  for(i=0;i<N;i++){
    norm2 += vec[i]*vec[i];
  }
#pragma omp single
{
  printf("pi = %f\n",norm2);
  norm = sqrt(norm2);
  norm2 = 0.;
}
#pragma omp for nowait schedule(static)
  for(i=0;i<N;i++){
    vec[i] /= norm;
  }
#pragma omp for schedule(static) reduction(+:norm2)
  for(i=0;i<N;i++){
    norm2 += vec[i]*vec[i];
  }
//#pragma omp barrier
#pragma omp master
  printf("pi = %f\n",norm2);
}
}
