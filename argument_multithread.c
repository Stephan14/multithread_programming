#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *task( void *argv )
{
    int *temp, count;
    temp = (int *)argv;

    for( count = 0; count < *temp; count++ )
        printf("work form thread: %d\n", count );
    printf("thread complie\n");

    return NULL;
}

int main(int argc, char const *argv[]) 
{
    int index;
    pthread_t myPthread[10];
    int num  = atoi( argv[1] ) > 10 ? 10: atoi( argv[1] );

    for( index = 0; index < num; index++  )
        pthread_create( &myPthread[index], NULL, task, &num );

    for( index = 0; index < num; index++ )
        pthread_join( myPthread[index], NULL );

    return 0;
}
