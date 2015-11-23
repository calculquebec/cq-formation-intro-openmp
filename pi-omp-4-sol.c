/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Date : Aout 2012
 *
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Approximation de PI par integration en utilisant OpenMP. Cet exemple est
 *   fonctionnel et suffisament rapide.
 */
#include <stdio.h>
#include <omp.h>

int main(void) {
  int nbThreads = 0, i = 0;
  long nbSteps = 3e8;
  double step = 1.0/(double)nbSteps;
  double pi = 0, sum = 0, x;

  #pragma omp parallel default(none)\
   shared(i,nbThreads,nbSteps,step) reduction(+:sum)
  {
    double x;

    #pragma omp master 
    nbThreads = omp_get_num_threads();
    #pragma omp for 
    for (i = 1; i <= nbSteps; ++i) {
      x = (i+0.5) * step;
      sum += 4.0 / (1.0 + x*x);
    }
  }
  pi = step * sum; 
  printf("Pi approximé à %.8f avec %d fils\n",pi, nbThreads);

}
