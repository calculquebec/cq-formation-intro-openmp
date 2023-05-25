#include <stdio.h>


long count_path_serial(int col, int row){
  if(col==1 || row==1) return 1;
  int i, j;
  i = count_path_serial(col-1, row);
  j = count_path_serial(col, row-1);
  return i + j;
}


long count_path_task(int col, int row){
  if (col==1 || row==1) return 1;
  if (col<=10 || row<=10) return count_path_serial(col, row);
  int i, j;
#pragma omp task shared(i)
  i = count_path_task(col-1, row);
#pragma omp task shared(j)
  j = count_path_task(col, row-1);
#pragma omp taskwait
  return i + j;
}


long count_path(int col, int row){
  long out;
  if(col==1 || row==1) return 1;
#pragma omp parallel
#pragma omp single
  out = count_path_task(col-1, row) + count_path_task(col, row-1);

  return out;
}

void main(){
  int col=18;
  int row=18;

  printf("Paths(%i, %i) = %ld\n", col, row, count_path(col, row));
}
