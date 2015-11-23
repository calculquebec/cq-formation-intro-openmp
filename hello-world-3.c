/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Date : Aout 2012
 * 
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Affiche, dans chacun des fils, le numero du fils courant puis, le nombre
 *   total de fils d'executions. Cette version contient un probleme de
 *   concurrence.
 */
#include <stdio.h>
#include <omp.h>

int main(void) {
    int nbThreads = 0;
    printf("Début de la section parallèle\n");

	#pragma omp parallel default(none) shared(nbThreads)
	{
	   #pragma omp master
	     nbThreads = omp_get_num_threads();
       printf("Hello world - fil #%d\n", omp_get_thread_num());
	}
    printf("Fin de la section parallèle de %d fils\n", nbThreads);
}

