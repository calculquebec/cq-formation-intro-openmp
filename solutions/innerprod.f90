PROGRAM innerprod

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: N = 10000000
INTEGER, ALLOCATABLE :: A(:), B(:), localips(:)
INTEGER :: ip, i, tid, localip
DOUBLE PRECISION :: t1, t2

    ALLOCATE(A(N),B(N),localips(OMP_GET_MAX_THREADS()))
    DO i = 1, N
       A(i) = 2
       B(i) = 3
    ENDDO

    t1 = OMP_GET_WTIME()
    ip = 0
!$OMP PARALLEL PRIVATE(i,tid,localip) SHARED (ip,A,B,localips)
    tid = OMP_GET_THREAD_NUM()
    localip = 0
!$OMP DO
    DO i = 1, N
       localip = localip + A(i) * B(i)
    ENDDO
!$OMP END DO NOWAIT
    localips(tid+1) = localip
!$OMP BARRIER
!$OMP SINGLE
    DO i = 1, OMP_GET_NUM_THREADS()
       ip = ip + localips(i)
    ENDDO
!$OMP END SINGLE
!$OMP END PARALLEL
    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Inner product = ', ip, 'Time =', t2 - t1

END PROGRAM innerprod
