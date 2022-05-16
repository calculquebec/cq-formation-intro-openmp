#include <stdio.h>
#include <omp.h>
#define MAX_NUM_THREADS 40

int main(void) {
int i, N=1000000000, fil_n, num_threads;
double Sum =0., sum[MAX_NUM_THREADS];

#pragma omp parallel private(fil_n)
  {
    fil_n = omp_get_thread_num();
    num_threads = omp_get_num_threads();
    sum[fil_n] = 0.;
#pragma omp for
    for(i=0;i<N;i+=2){
      sum[fil_n] += 4./(2.*i+1.);
      sum[fil_n] -= 4./(2.*i+3.);
    }
  }
  for(i=0;i<num_threads;i++){
    Sum += sum[i];
  }
  printf("pi = %f\n",Sum);
}
