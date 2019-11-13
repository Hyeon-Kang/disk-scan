// 교착상태 만들어보기

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//printf("A 스레드의 작업 결과를 기다리는 중\n");
//printf("B 스레드의 작업 결과를 기다리는 중\n");

// 공유자원
int a =10;
int b = 5;

// 뮤텍스 선언
pthread_mutex_t mutex;

void function_a()
{
      b += 5;
      printf("function_a : b+=5 : %d\n", b);
      sleep(1);
      printf("a 접근 대기중\n");
      pthread_mutex_lock(&mutex);
      a +=5;
      sleep(30);
      pthread_mutex_unlock(&mutex);
      printf("function_a : a+=5 : %d\n", a);

      printf("작업완료\n");
}

void function_b()
{
      a += 5;
      printf("function_b : a+=5\n");
      sleep(1);
      printf("b 접근 대기중\n");
      pthread_mutex_lock(&mutex);
      b +=5;
      sleep(30);
      pthread_mutex_unlock(&mutex);
      printf("function_b : b+=5\n");

      printf("작업완료\n");
}

int main() {
      pthread_t p1, p2;

      pthread_mutex_init(&mutex, NULL);

      pthread_create(&p1, NULL, *function_a, NULL);
      pthread_create(&p2, NULL, *function_b, NULL);

      pthread_join(p1, NULL);
      pthread_join(p2, NULL);

      return 0;
}
