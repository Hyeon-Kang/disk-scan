/* 목표
    2개의 스레드 작성
    각 스레드는 StudentInfor 구조체를 전달받음
    구조체 : name, major, univ  모두 char
    	‘stu1’ = {“Kang Daniel”, “Computer Engineering”, “101 University”}
    	‘stu2’ = {“Kim Da-hyun”, “Computer Science”, “TWICE University”}

    ‘start_thread’ 함수는 for-loop에서 name, major, univ 정보를 출력하며,
    for-loop은 0부터 9까지 총 10번을 반복한다.
*/
// pthread에 구조체 인자 전달
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *print_structure(void *);

typedef struct{
  char name[20];
  char major[30];
  char univ[30];
} thread_args;

int main(void) {
  pthread_t t1, t2;

  // stu1 구조체 선언
  thread_args stu1;
  strcpy(stu1.name, "Kang Daniel");
  strcpy(stu1.major, "Computer Engineering");
  strcpy(stu1.univ, "101 Universiry");

  // stu2 구조체 선언
  thread_args stu2;
  strcpy(stu2.name, "Kim Da-hyun");
  strcpy(stu2.major, "Computer Science");
  strcpy(stu2.univ, "TWICE Universiry");

  // Pthread 실행
  pthread_create(&t1, NULL, print_structure, &stu1);
  pthread_create(&t2, NULL, print_structure, &stu2);

  // Pthread join(wait)
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}

// thread 실행 함수
void *print_structure(void *arg) {
  // void 형태로 전달한 인자를 구조체로 재정의
  thread_args *args = (thread_args *) arg;

  printf("%s\n", args->name);
  printf("%s\n", args->major);
  printf("%s\n", args->univ);
  printf("\n");

  return NULL;
}
