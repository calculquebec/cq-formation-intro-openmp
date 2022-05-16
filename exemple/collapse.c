#include <stdio.h>
#include <omp.h>

#define SIZE 500

double f(int i, int j){
	if (i<=1) return j;
	if (j<=1) return i;
	return f(i,j/2)+f(i/2,j)-f(i/2-j/2,j/2-i/2);
}

int main(void) {
  int i,j, N=SIZE;
  double A[SIZE][SIZE];
#pragma omp parallel for collapse(2) private(i,j) shared(A) schedule(dynamic)
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
       A[i][j]=f(i,j);
    }
  }
  
  printf("%f, %f, %f %f \n",A[0][0],A[0][N-1],A[N-1][0],A[N-1][N-1]);
}
