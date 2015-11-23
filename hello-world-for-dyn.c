/**
 * Auteur : Frederick Lefebvre <frederick.lefebvre@calculquebec.ca>
 * Révision : Laurent Duchesne <laurent.duchesne@calculquebec.ca>
 * Date : Aout 2012, Novembre 2015
 * 
 * Historique :
 *   - Version initiale de l'exemple.
 *
 * Description :
 *   Affiche, dans chacun des fils d'execution, le numero du fils courant ainsi
 *   que le nombre total de fils d'executions.
 *
 *   Cet exemple demontre l'utilisation du #pragma omp for.
 */
#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(void)
{
    int nbThreads = 0, i = 0;
    printf("Début de la section parallèle\n");

    #pragma omp parallel default(none) shared(nbThreads,i)
    {
        #pragma omp single
        nbThreads = omp_get_num_threads();

        #pragma omp for schedule(dynamic,2)
        for (i=0 ; i<16 ; ++i) {
            printf("Hello world - fil #%d de %d a i=%d\n", omp_get_thread_num(),nbThreads,i);
        }
    }

    printf("Fin de la section parallèle de %d fils\n", nbThreads);
}
