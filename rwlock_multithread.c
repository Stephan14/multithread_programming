#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<pthread.h>

#define BUFFER_MAX 1024

pthread_rwlock_t rwlock;
char work_buffer[ BUFFER_MAX ];
int time_to_exit = 0;

void *thread_read_o( void * argc )
{
  while( strncmp( "end", work_buffer, 3 ) != 0 )
  {
    sleep( 1 );
    pthread_rwlock_rdlock( &rwlock );
    printf("read pthread_o get read lock.\n");
    printf("read pthread_o get buffer: %s", work_buffer );
    printf("read pthread_o release read lock.\n");
    pthread_rwlock_unlock( &rwlock );
  }

  time_to_exit = 1;
  pthread_exit( NULL );
}

void *thread_read_t( void * argc )
{
  while( strncmp( "end", work_buffer, 3 ) != 0 )
  {
    sleep( 5 );
    pthread_rwlock_rdlock( &rwlock );
    printf("read pthread_t get read lock.\n");
    printf("read pthread_t get buffer: %s", work_buffer );
    printf("read pthread_t release read lock.\n");
    pthread_rwlock_unlock( &rwlock );
  }

  time_to_exit = 1;
  pthread_exit( NULL );
}

void *thread_wirte_o( void *argc )
{
  while( !time_to_exit )
  {
    pthread_rwlock_wrlock( &rwlock );
    printf("write pthread_o get write lock.\n");
    printf("write pthread_o intput.\n");
    fgets( work_buffer, BUFFER_MAX, stdin );
    printf("user input in write pthread_o %s\n", work_buffer );
    printf("write pthread_o release write lock.\n");
    pthread_rwlock_unlock( &rwlock );
    sleep( 4 );
  }
  pthread_exit( NULL );
}

void *thread_wirte_t( void *argc )
{
  while( !time_to_exit )
  {
    pthread_rwlock_wrlock( &rwlock );
    printf("write pthread_t get write lock.\n");
    printf("write pthread_t intput.\n");
    fgets( work_buffer, BUFFER_MAX, stdin );
    printf("user input in write pthread_t %s", work_buffer );
    sleep( 5 );
    printf("write pthread_t release write lock.\n");
    pthread_rwlock_unlock( &rwlock );
  }
  pthread_exit( NULL );
}

int main(int argc, char const *argv[]) {
  int res;
  pthread_t p1, p2, p3, p4;
  void *thread_result;

  res = pthread_rwlock_init( &rwlock, NULL );
  if( res != 0 )
  {
    printf("pthread init error\n");
    exit(0);
  }

  res = pthread_create( &p1, NULL, thread_read_o, NULL );
  if( res != 0 )
  {
    printf("pthread create error\n");
    exit(0);
  }

  res = pthread_create( &p2, NULL, thread_read_t, NULL );
  if( res != 0 )
  {
    printf("pthread create error\n");
    exit(0);
  }

  res = pthread_create( &p3, NULL, thread_wirte_o, NULL );
  if( res != 0 )
  {
    printf("pthread create error\n");
    exit(0);
  }

  // res = pthread_create( &p4, NULL, thread_wirte_t, NULL );
  // if( res != 0 )
  // {
  //   printf("pthread create error\n");
  //   exit(0);
  // }

  res = pthread_join( p1, &thread_result );//等待a_thread线程结束
  if(res != 0 )
  {
    printf("Thread join failed");
    exit(0);
  }

  res = pthread_join( p2, &thread_result );//等待a_thread线程结束
  if(res != 0 )
  {
    printf("Thread join failed");
    exit(0);
  }

  res = pthread_join( p3, &thread_result );//等待a_thread线程结束
  if(res != 0 )
  {
    printf("Thread join failed");
    exit(0);
  }

  // res = pthread_join( p4, &thread_result );//等待a_thread线程结束
  // if(res != 0 )
  // {
  //   printf("Thread join failed");
  //   exit(0);
  // }

  pthread_rwlock_destroy( &rwlock );
  return 0;
}
