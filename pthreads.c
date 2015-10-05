#include <stdio.h>
#include <pthread.h>

#define SIZE 4

void *hello(void *arg)
{
    printf( "Hello from processor %d of %d\n", *(int *)arg, SIZE );
    return NULL;
}

int main(int argc, char* argv[]) {
    int i, p[SIZE];
    pthread_t threads[SIZE];

    /* Fork threads */
    for (i = 1; i < SIZE; i++) {
        p[i] = i;
        pthread_create(&threads[i], NULL, hello, &p[i]);
    }

    p[0] = 0;
    hello(&p[0]); /* thread 0 greets as well */

    /* Join threads. */
    for (i = 1; i < SIZE; i++)
        pthread_join(threads[i], NULL);
    return 0;
}
