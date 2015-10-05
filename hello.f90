PROGRAM hello

!$ USE omp_lib

IMPLICIT NONE
INTEGER rank, size

rank = 0
size = 1

!$OMP PARALLEL PRIVATE(rank, size)

!$  size = omp_get_num_threads()

!$  rank = omp_get_thread_num()
   
    WRITE(*,*) 'Hello from processor ', rank, ' of ', size

!$OMP END PARALLEL
    
END PROGRAM hello
