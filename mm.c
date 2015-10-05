/******************************************************************************
* FILE: mm.c
* DESCRIPTION:  
*   OpenMp Example - Matrix Multiply - C Version
*   Demonstrates a matrix multiply using OpenMP. Threads share row iterations
*   according to a predefined chunk size.
* ORIGINAL AUTHOR: Blaise Barney
* LAST REVISED: 2/28/13 Bart Oldeman
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NRA 62                 /* number of rows in matrix A */
#define NCA 15                 /* number of columns in matrix A */
#define NCB 7                  /* number of columns in matrix B */

int main (void)
{
  int   tid, nthreads, i, j, k;
  double a[NRA][NCA],           /* matrix A to be multiplied */
         b[NCA][NCB],           /* matrix B to be multiplied */
         c[NRA][NCB];           /* result matrix C */

  tid = 0;
  nthreads = 1;

  printf("Starting matrix multiple example with %d threads\n",nthreads);
  printf("Initializing matrices...\n");

  /*** Initialize matrices ***/
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do matrix multiply sharing iterations on outer loop ***/
  /*** Display who does which iterations for demonstration purposes ***/
  printf("Thread %d starting matrix multiply...\n",tid);
  for (i=0; i<NRA; i++)    
  {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<NCB; j++)
      for (k=0; k<NCA; k++)
        c[i][j] += a[i][k] * b[k][j];
  }

  /*** Print results ***/
  printf("******************************************************\n");
  printf("Result Matrix:\n");
  for (i=0; i<NRA; i++)
    {
      for (j=0; j<NCB; j++)
        printf("%8.2f  ", c[i][j]);
      printf("\n");
    }
  printf("******************************************************\n");
  printf ("Done.\n");
  return 0;
}
