#include <stdio.h>

long count_path(int col, int row){
  if(col==1 || row==1) return 1;
  return count_path(col-1, row) + count_path(col, row-1);
}

void main(){
  int col=18;
  int row=18;

  printf("Paths(%i, %i) = %ld\n", col, row, count_path(col, row));
}
