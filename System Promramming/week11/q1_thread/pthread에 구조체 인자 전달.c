// pthread에 구조체 인자 전달
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *print_structure(void *);

typedef struct{
  int n;
  int m;
} thread_args;

int main(void) {
  pthread_t t;

  int n =10;
  int m =20;
  thread_args thr;

  thr.n = n;
  thr.m = m;

  pthread_create(&t, NULL, print_structure, &thr);
  pthread_join(t, NULL);

  return 0;
}

void *print_structure(void *arg) {
  thread_args *args = (thread_args *) arg;
  int n = args->n;
  int m = args->m;
  int i;

  for(i=n; i<m; i++) {
      printf("%d\n", i);
  }

  return NULL;
}
