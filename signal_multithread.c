#include<stdio.h>
#include<pthread.h>
#include<errno.h>

#define BOUND 5

int task = 10;
pthread_mutex_t task_mutex;
pthread_cond_t task_cond;

void *say_hello2( void *args )
{
  pthread_t pid = pthread_self();
  printf("pthread %d run sayhello2 with %d \n", pid, *( ( int *) args ) );

  while(1)
  {
    pthread_mutex_lock( &task_mutex );

    if( task > BOUND )
      printf("before pthread %d with %d subtract one task is %d\n", pid, *( ( int *) args ), task-- );
    else
    {
      printf("no __ pthread %d pthread_cond_signal other thread %d\n", pid, *( ( int *) args ));
      pthread_cond_signal( &task_cond );//通知等待的进程
    }

    pthread_mutex_unlock( &task_mutex );

    if( task == 0 )
      break;
  }
  return NULL;
}

void *say_hello1( void *args )
{
  pthread_t pid = pthread_self();

  printf("pthread %d run sayhello1 with %d \n", pid, *( ( int *) args ) );
  int is_send_signal = 0;
  while(1)
  {
    pthread_mutex_lock( &task_mutex );

    if( task > BOUND )
    {
      printf("pthread %d with %d pthread_cond_wait when task is %d \n", pid, *( ( int *) args ), task );
      pthread_cond_wait( &task_cond, &task_mutex );
    }
    else
      printf("before pthread %d with %d subtract one task is %d\n", pid, *( ( int *) args ), task-- );

    pthread_mutex_unlock( &task_mutex );
    if( task == 0 )
      break;
  }
  return NULL;
}
int main(int argc, char const *argv[]) {
  int state;
  pthread_t pthread1, pthread2;
  pthread_attr_t attr;
  pthread_attr_init( &attr );
  pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
  pthread_mutex_init( &task_mutex, NULL );
  pthread_cond_init( &task_cond, NULL );

  int index1 = 1;
  if(( state = pthread_create( &pthread1, &attr, say_hello1, (void *)&index1 ) ) != 0 )
    printf("pthread_create error !\n");
  int index2 = 1;
  if(( state = pthread_create( &pthread2, &attr, say_hello2, (void *)&index2 ) ) != 0 )
    printf("pthread_create error !\n");

  pthread_join( pthread1, NULL );
  pthread_join( pthread2, NULL );
  pthread_mutex_destroy( &task_mutex );
  pthread_cond_destroy( &task_cond );
  pthread_attr_destroy( &attr );
  return 0;
}
