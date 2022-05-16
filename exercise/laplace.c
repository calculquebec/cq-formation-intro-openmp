#include <stdio.h>
#include <omp.h>
#include <math.h>

#define SIZE 500

int main(void){
  double *T,*Tmp,*Tnew;
  double T1[SIZE+2][SIZE+2];
  double T2[SIZE+2][SIZE+2];
  double var=1, tol=0.001;
  double x;
  int i, j, iter=0, maxIter=2000;
  T = &T1[0][0];
  Tnew = &T2[0][0];
  int n=SIZE, n2=SIZE+2;
  
  // Conditions initiales
  for (i=1; i<=n; ++i){
	x = i*1./(SIZE+1);
    T[i] = x*(1-x)*2;
    T[i*n2] = -1.5*x*(1-x)+x;
    T[i*n2+n+1] = 3.*x;
    T[(n+1)*n2+i] = 1-x+x*x*3.;
    for (j=1; j<=n; ++j){
      T[i*n2+j] = 0.;
    }
  }
  for (i=0; i<n2; ++i)
    for (j=0; j<n2; ++j)
       Tnew[i*n2+j] = T[i*n2+j];
  
  while(var > tol && iter < maxIter) {
    ++iter;
    var = 0.0;
    for (i=1; i<=n; ++i)
      for (j=1; j<=n; ++j) {
        Tnew[i*n2+j] = 0.25*(T[(i-1)*n2+j] +T[(i+1)*n2+j]
                            +T[i*n2+(j-1)] +T[i*n2+(j+1)]);
        var = fmax(var, fabs(Tnew[i*n2+j] - T[i*n2+j]));
    }
    Tmp=T; T=Tnew; Tnew=Tmp;
    if (iter%100 == 0)
    printf("iter: %8u, variation = %12.4lE\n", iter, var);
  }
  printf("iter: %8u, variation = %12.4lE\n", iter, var);
}
