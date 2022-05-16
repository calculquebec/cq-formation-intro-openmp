#include <stdio.h>
#include <omp.h>

int main(void) {
   printf("Début de la section parallèle\n");
   omp_set_num_threads(4);
#pragma omp parallel
  {
     printf("Hello world - fil #%d de %d\n",
     omp_get_thread_num(),omp_get_num_threads());
  }

  printf("Fin de la section parallèle\n");
}
