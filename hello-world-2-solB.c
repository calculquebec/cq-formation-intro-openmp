/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Date : Aout 2012
 * 
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Affiche, dans chacun des fils, le numero du fils courant puis, le nombre
 *   total de fils d'executions.
 */
#include <stdio.h>
#include <omp.h>

int main(void) {
    int nbThreads = 0;
    printf("Début de la section parallèle\n");

	#pragma omp parallel
	{
	   int noThread = -1;
	   noThread = omp_get_thread_num();
		if (noThread == 0)
		    nbThreads = omp_get_num_threads();
	    
        printf("Hello world - fil #%d\n", noThread);
	}
    printf("Fin de la section parallèle de %d fils\n", nbThreads);
}

