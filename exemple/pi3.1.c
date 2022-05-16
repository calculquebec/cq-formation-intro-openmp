#include <stdio.h>
#include <omp.h>

int main(void) {
int i, N=1000000000, fil_n;
double sum=0., pi_fil;

#pragma omp parallel private(pi_fil)
{
  pi_fil= 0.;
#pragma omp for
  for(i=0;i<N;i+=2){
    pi_fil += 4./(2.*i+1.);
    pi_fil -= 4./(2.*i+3.);
  }
#pragma omp atomic
  sum += pi_fil;
}

printf("pi = %f\n",sum);
}
