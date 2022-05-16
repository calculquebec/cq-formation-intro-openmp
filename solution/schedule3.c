#include <stdio.h>
#include <omp.h>
#include <unistd.h>

#define N 100

int main(void) {
printf("schedule(static, 2)\n");
#pragma omp parallel
  {
    char done_here[N+1];
    done_here[N] = 0;
    for(int i=0; i<N; i++){done_here[i] = '.';}
#pragma omp for schedule(static, 2)
    for(int i=0; i<N; i++){
      usleep(1000*((i*i)%10));
      done_here[i] = 'o';
    }
#pragma omp critical
  printf("Fil %d: %s \n", omp_get_thread_num(), done_here);
  }


printf("schedule(dynamic, 2)\n");
#pragma omp parallel
  {
    char done_here[N+1];
    done_here[N] = 0;
    for(int i=0; i<N; i++){done_here[i] = '.';}
#pragma omp for schedule(dynamic, 2)
    for(int i=0; i<N; i++){
      usleep(1000*((i*i)%10));
      done_here[i] = 'o';
    }
#pragma omp critical
  printf("Fil %d: %s \n", omp_get_thread_num(), done_here);
  }

printf("schedule(guided, 2)\n");
#pragma omp parallel
  {
    char done_here[N+1];
    done_here[N] = 0;
    for(int i=0; i<N; i++){done_here[i] = '.';}
#pragma omp for schedule(guided, 2)
    for(int i=0; i<N; i++){
      usleep(1000*((i*i)%10));
      done_here[i] = 'o';
    }
#pragma omp critical
  printf("Fil %d: %s \n", omp_get_thread_num(), done_here);
  }
}
