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
  pthread_create( &pthreadA, NULL, PthreadA, NULL );
  pthread_create( &pthreadB, NULL, PthreadB, NULL );

  pthread_join( pthreadA, NULL );
  pthread_join( pthreadB, NULL );
  return 0;
}
