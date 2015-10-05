!******************************************************************************
! FILE: mm.f90
! DESCRIPTION:  
!   OpenMp Example - Matrix Multiply - Fortran Version 
!   Demonstrates a matrix multiply using OpenMP. Threads share row iterations
!   according to a predefined chunk size.
! ORIGINAL AUTHOR: Blaise Barney
! LAST REVISED: 2/28/13 Bart Oldeman
!******************************************************************************

PROGRAM MATMULT

  USE OMP_LIB
  IMPLICIT NONE
  INTEGER tid, nthreads, i, j, k, chunk

  INTEGER, PARAMETER :: NRA = 62 ! number of rows in matrix A 
  INTEGER, PARAMETER :: NCA = 15 ! number of columns in matrix A
  INTEGER, PARAMETER :: NCB = 7  ! number of columns in matrix B

  DOUBLE PRECISION A(NRA,NCA), B(NCA,NCB), C(NRA,NCB)

! Set loop iteration chunk size 
  chunk = 10

! Spawn a parallel region explicitly scoping all variables
!$OMP PARALLEL SHARED(A,B,C,nthreads,chunk) PRIVATE(TID,i,j,K)
  tid = OMP_GET_THREAD_NUM()
  IF (tid == 0) THEN
     nthreads = OMP_GET_NUM_THREADS()
     PRINT *, 'Starting matrix multiple example with', nthreads, &
                'threads'
     PRINT *, 'Initializing matrices'
  END IF

  ! Initialize matrices
!$OMP DO SCHEDULE(STATIC, chunk)
  DO i=1, NRA
     DO j=1, NCA
        A(i,j) = (i-1)+(j-1)
     ENDDO
  ENDDO
!$OMP DO SCHEDULE(STATIC, chunk)
  DO i=1, NCA
     DO j=1, NCB
        B(i,j) = (i-1)*(j-1)
     ENDDO
  ENDDO
!$OMP DO SCHEDULE(STATIC, chunk)
  DO i=1, NRA
     DO j=1, NCB
        C(i,j) = 0
     ENDDO
  ENDDO

! Do matrix multiply sharing iterations on outer loop
! Display who does which iterations for demonstration purposes
  PRINT *, 'Thread', tid, 'starting matrix multiply...'
!$OMP DO SCHEDULE(STATIC, chunk)
  DO i=1, NRA
     PRINT *, 'Thread', tid, 'did row', i
     DO j=1, NCB
        DO k=1, NCA
           C(i,j) = C(i,j) + A(i,k) * B(k,j)
        ENDDO
     ENDDO
  ENDDO

! End of parallel region 
!$OMP END PARALLEL

! Print results
  PRINT *, '******************************************************'
  PRINT *, 'Result Matrix:'
  DO i=1, NRA
     WRITE(*,"(7f10.2)") (C(i,j),j=1,NCB)
  ENDDO
  PRINT *, '******************************************************'
  PRINT *, 'Done.'

END PROGRAM MATMULT
