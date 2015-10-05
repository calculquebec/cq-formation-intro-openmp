!******************************************************************************
! FILE: omp_bug1.f
! DESCRIPTION:
!   This example attempts to show use of the PARALLEL DO construct.  However
!   it will generate errors at compile time.  Try to determine what is causing
!   the error.  See omp_bug1fix.f for a corrected version.
! AUTHOR: Blaise Barney  5/99
! LAST REVISED: 
!******************************************************************************

PROGRAM WORKSHARE3

  USE OMP_LIB
  IMPLICIT NONE
  INTEGER tid, i, chunk
  INTEGER, PARAMETER :: N=50, CHUNKSIZE=5
  REAL A(N), B(N), C(N)

!     Some initializations
  DO i = 1, N
     A(i) = i * 1.0
     B(i) = A(i)
  ENDDO
  chunk = CHUNKSIZE
            
!$OMP PARALLEL SHARED(A,B,C,chunk) PRIVATE(i,tid)

  tid = OMP_GET_THREAD_NUM()
!$OMP DO SCHEDULE(STATIC,chunk)
  DO i = 1, N
     C(i) = A(i) + B(i)
     PRINT *,'tid= ',tid,'i= ',i,'C(i)= ',C(i)
  ENDDO

!$OMP END DO
!$OMP END PARALLEL

END PROGRAM WORKSHARE3
