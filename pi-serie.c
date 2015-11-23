/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Date : Aout 2012
 *
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Version serie d'une approximation de PI par integration.
 */
#include <stdio.h>

int main(void) {
  static long nbSteps = 3e8;
  int i;
  double step = 1.0/(double)nbSteps;
  double pi = 0, sum = 0, x;

  for (i = 1; i <= nbSteps; ++i) {
    x = (i+0.5) * step;
	sum = sum + 4.0 / (1.0 + x*x);
  }
  pi = step * sum; 
  printf("Pi approximé à %.8f\n",pi);

}
