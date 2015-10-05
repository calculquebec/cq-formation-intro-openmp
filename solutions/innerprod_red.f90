PROGRAM innerprod

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: N = 10000000
INTEGER, ALLOCATABLE :: A(:), B(:)
INTEGER :: ip, i
DOUBLE PRECISION :: t1, t2

    ALLOCATE(A(N),B(N))
    DO i = 1, N
       A(i) = 2
       B(i) = 3
    ENDDO

    t1 = OMP_GET_WTIME()
    ip = 0
!$OMP PARALLEL DO REDUCTION(+:ip)
    DO i = 1, N
       ip = ip + A(i) * B(i)
    ENDDO
!$OMP END PARALLEL DO
    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Inner product = ', ip, 'Time =', t2 - t1

END PROGRAM innerprod
