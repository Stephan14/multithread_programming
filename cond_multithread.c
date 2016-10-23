#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_cond_t full = PTHREAD_COND_INITIALIZER, empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int buffer[4];
int begin = 0, end = 0, counter = 0, max = 4;

void *producer( void *arg ){
  printf("pthread producer id : %d run \n", *(int *) arg );
  srand(1);
  while( 1 )
  {
    pthread_mutex_lock( &mutex );//一定要加锁
    while( counter == max )
      pthread_cond_wait( &full, &mutex );
    buffer[ end ] = rand()%10;
    counter++;
    printf("pthread producer id :%d produce at %d and counter is %d\n", *(int *) arg, buffer[ end ], counter );
    end = ++end % max;
    pthread_mutex_unlock( &mutex );
    pthread_cond_signal( &empty );
  }
  return NULL;
}


void *consumer( void *arg )
{
  printf("pthread consumer id : %d run \n", *(int *)arg );
  while( 1 )
  {
    pthread_mutex_lock( &mutex );//一定要先加锁
    while( counter == 0 )
      pthread_cond_wait( &empty, &mutex );
    counter--;
    printf("pthread consumer id :%d consumer at %d and counter is %d\n", *(int *) arg, buffer[ begin ], counter );
    begin = ++begin % max;
    pthread_mutex_unlock( &mutex );
    pthread_cond_signal( &full );
  }
  return NULL;
}


int main(int argc, char const *argv[]) {
  pthread_t pthread_consumer[3];
  pthread_t pthread_producer[2];
  int index = 0, *p = NULL ;
  for( index = 0; index < 3; index++ )
  {
    p = (int *)malloc( sizeof(int) );
    *p = index;
    if( pthread_create( &pthread_consumer[ index ], NULL, producer, p ) != 0)
    {
      printf("create consumer error\n");
      return -1;
    }
  }

  for( index = 0; index < 2; index++ )
  {
    p = (int *)malloc( sizeof(int) );
    *p = index;
    if( pthread_create( &pthread_producer[ index ], NULL, consumer, p ) != 0)
    {
      printf("create consumer error\n");
      return -1;
    }
  }
  for( index = 0; index < 3; index++ )
    pthread_join( pthread_consumer[ index ], NULL  );

  for( index = 0; index < 2; index++ )
    pthread_join( pthread_producer[ index ], NULL );

  return 0;
}
