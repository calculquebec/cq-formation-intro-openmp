#include <stdio.h>
#include <omp.h>


void swap(double *x, double *y){
    double temp = *x;
    *x = *y;
    *y = temp;
}


int partition(double array[], int low, int high){
    double pivot = array[high];
    int i = low;

    for(int j=low; j<=high-1; j++) {
        if (array[j] <= pivot){
           swap(&array[i], &array[j]);
           i++;
        }
    }
    swap(&array[i], &array[high]);
    return i;
}


void quicksort(double array[], int low, int high){
    int pi;
    if(high-low <= 0){return;}
    if(high-low <= 1000){
        pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    } else {
        pi = partition(array, low, high);
        #pragma omp task shared(array, pi, high)
        quicksort(array, low, pi - 1);
        #pragma omp task shared(array, pi, high)
        quicksort(array, pi + 1, high);
    }
}


void main(){
  const int N=1000000;
  double array[N];
  double c_start, c_end;

  for(int i=0; i<N; i++){
      array[i] = ((i * 2) % N) * 1. / N + ((i * i * 10) % N)* 1. / N - (i % 1234) / 1234.;
  }
  c_start = omp_get_wtime();
#pragma omp parallel shared(array, N)
#pragma omp single
  quicksort(array, 0, N-1);

  c_end = omp_get_wtime();
  printf("time: %f ms \n", 1000.0 * (c_end - c_start));
}
