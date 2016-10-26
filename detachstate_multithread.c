#include<stdio.h>
#include<pthread.h>

void *PthreadA( void * a)
{
  printf("PthreadA run ...\n");
  printf("PthreadA end ...\n");
  return NULL;
}

void *PthreadB( void * b)
{
  printf("PthreadB run ...\n");
  printf("PthreadB end ...\n");
  return NULL;
}

int main(int argc, char const *argv[]) {
  pthread_t pthreadB, pthreadA;
  pthread_attr_t detach_attr;

  pthread_attr_init( &detach_attr );
  pthread_attr_setdetachstate( &detach_attr, PTHREAD_CREATE_DETACHED );
  pthread_create( &pthreadA, &detach_attr, PthreadA, NULL );
  pthread_create( &pthreadB, NULL, PthreadB, NULL );

  pthread_detach( pthreadB );
  //pthread_join( pthreadA, NULL );
  //pthread_join( pthreadB, NULL );
  return 0;
}
