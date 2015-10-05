PROGRAM PI_collect

USE omp_lib
IMPLICIT NONE

DOUBLE PRECISION pi
INTEGER n, i

DOUBLE PRECISION, PARAMETER :: PI25 = 3.141592653589793d0

    DO
        WRITE(*,*) 'Enter the number of intervals (0 quits) : '
        READ(*,*) n

        IF ( n <= 0 ) EXIT

        pi = 0.0d0
!$OMP PARALLEL DO PRIVATE(i) REDUCTION(+:pi)
        DO i = n - 1, 0, -1
            pi = pi + (4.0d0 - ISHFT(MOD(i, 2), 3)) / (2 * DBLE(i) + 1)
        ENDDO
!$END OMP

        WRITE(*, "(' Pi is approximately: ', F19.16, ' Error is: ', F19.16)") pi, ABS(pi - PI25)
    ENDDO

END PROGRAM pi_collect
