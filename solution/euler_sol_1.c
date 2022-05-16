#include <stdio.h>
#include <omp.h>
#define N 100

int main(void) {
  int i, n_threads;
  double fact[N], Sum=0., sum[16*8];
 
  fact[0]=1;
  for(i=1;i<N;i++){
    fact[i] = i*fact[i-1];
  }
  
#pragma omp parallel
  {
  int n_fil = omp_get_thread_num();
#pragma omp master
  n_threads = omp_get_num_threads();
  sum[n_fil*8] = 0.;
#pragma omp for 
  for(i=0;i<N;i++){
    sum[n_fil*8] += 1./fact[i];
  }
  }

  for(i=0;i<n_threads;++i){ 
     Sum += sum[i*8];
  }
  printf("The sum is %f\n",Sum);
}
