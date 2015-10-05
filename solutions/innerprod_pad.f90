PROGRAM innerprod

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: N = 10000000, PAD=16
INTEGER, ALLOCATABLE :: A(:), B(:), localips(:,:)
INTEGER :: ip, i, tid
DOUBLE PRECISION :: t1, t2

    ALLOCATE(A(N),B(N),localips(PAD,0:OMP_GET_MAX_THREADS()-1))
!$OMP PARALLEL DO DEFAULT(none) PRIVATE(i) SHARED (A,B)
    DO i = 1, N
       A(i) = 2
       B(i) = 3
    ENDDO
!OMP END PARALLEL DO

    t1 = OMP_GET_WTIME()
    ip = 0
!$OMP PARALLEL DEFAULT(none) PRIVATE(i,tid) SHARED (ip,A,B,localips)
    tid = OMP_GET_THREAD_NUM()
    localips(1,tid) = 0
!$OMP DO
    DO i = 1, N
       localips(1,tid) = localips(1,tid) + A(i) * B(i)
    ENDDO
!$OMP END DO
!$OMP SINGLE
    DO i = 0, OMP_GET_NUM_THREADS()-1
       ip = ip + localips(1,i)
    ENDDO
!$OMP END SINGLE
!$OMP END PARALLEL
    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Inner product = ', ip, 'Time =', t2 - t1

END PROGRAM innerprod
