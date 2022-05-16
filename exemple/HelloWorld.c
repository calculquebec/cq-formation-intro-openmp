#include <stdio.h>
#include <omp.h>

int main(void) {
   printf("Début de la section parallèle\n");

#pragma omp parallel
  {
     printf("Hello world - fil #%d de %d\n",
     omp_get_thread_num(),omp_get_num_threads());
  }

  printf("Fin de la section parallèle\n");
}
