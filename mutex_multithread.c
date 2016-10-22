#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int sum = 0;
pthread_mutex_t sum_mutex;

void *calculate( void * arg )
{
    printf("thread %d  run ...\n", *( (int *)arg ) );
    printf("before calculate in thread %d sum is %d\n", *( (int *)arg ), sum );

    pthread_mutex_lock( &sum_mutex );
    
    sum += *( (int *)arg );
    
    pthread_mutex_unlock( &sum_mutex );
    
    printf("after calculate in thread %d sum is %d\n", *( (int *)arg ), sum );
    printf("thread %d  run ...\n", *( (int *)arg ) );
    
    return NULL;
}

int main(int argc, char const *argv[]) 
{
    pthread_t myPhtread[10];
    pthread_attr_t attr;
    
    int index, indexs[10];
    int state;
    int count = atoi( argv[1] ) > 10? 10: atoi( argv[1] );

    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

    pthread_mutex_init( &sum_mutex, NULL );
  
    for( index = 0; index < count; index++ )
    {
        indexs[ index ] = index;
        if( ( state = pthread_create( &myPhtread[index], &attr, calculate, ( void *)&indexs[index] ) ) != 0)
            printf("pthread_create error !\n");
    }
    
    pthread_attr_destroy( &attr );

    for( index = 0; index < count; index++ )
        if( ( state = pthread_join( myPhtread[index], NULL ) ) != 0)
            printf("pthread_join error !\n");

    pthread_mutex_destroy( &sum_mutex );
    printf("finally sum is %d\n", sum );
    return 0;
}
