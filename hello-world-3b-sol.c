/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Date : Aout 2012
 * 
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Affiche, dans chacun des fils d'execution, le numero du fils courant ainsi
 *   que le nombre total de fils d'executions.
 */
#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(void) {
    int nbThreads = 0;
    printf("Début de la section parallèle\n");

	#pragma omp parallel default(none) shared(nbThreads)
	{
	   #pragma omp single 
	     nbThreads = omp_get_num_threads();

       printf("Hello world - fil #%d de %d\n", 
	          omp_get_thread_num(),nbThreads);
	}
    printf("Fin de la section parallèle de %d fils\n", nbThreads);
}

