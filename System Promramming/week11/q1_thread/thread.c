/* 목표
    2개의 스레드 작성
    각 스레드는 StudentInfor 구조체를 전달받음
    구조체 : name, major, univ  모두 char
    	‘stu1’ = {“Kang Daniel”, “Computer Engineering”, “101 University”}
    	‘stu2’ = {“Kim Da-hyun”, “Computer Science”, “TWICE University”}

    ‘start_thread’ 함수는 for-loop에서 name, major, univ 정보를 출력하며,
    for-loop은 0부터 9까지 총 10번을 반복한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

struct StudentInfor {
  char name[20];
  char major[30];
  char univ[30];
};

void print_StudentInfor (struct StudentInfor stud) {
    printf("name : %s\n", (const char*)stud.name);
    printf("major : %s\n", (const char*)stud.major);
    printf("univ : %s\n", (const char*)stud.univ);
}

void *start_thread(struct StudentInfor stud) {
  //int i;
  for(int i =0; i<10; i++) {
    sleep(1);
    print_StudentInfor(struct StudentInfor stud);
    //printf("name : %s\n", (const char*)stud.name);
    //printf("major : %s\n", (const char*)stud.major);
    //printf("univ : %s\n", (const char*)stud.univ);
    //sleep(1);
  }
  //return stud;
}

int main(int argc, char* argv[]) {

/*
  struct StudentInfor {
    char name[] = "Kang Daniel";
    char major[] = "Computer Engineering";
    char univ[] = "101 Universiry";
  } stu1;

  struct StudentInfor {
    char name[] = "Kim Da-hyun";
    char major[] = "Computer Science";
    char univ[] = "TWICE Universiry";
  } stu2;
*/
  struct StudentInfor stu1;
  struct StudentInfor stu2;

  strcpy(stu1.name, "Kang Daniel");
  strcpy(stu1.major, "Computer Engineering");
  strcpy(stu1.univ, "101 Universiry");

  strcpy(stu2.name, "Kim Da-hyun");
  strcpy(stu2.major, "Computer Science");
  strcpy(stu2.univ, "TWICE Universiry");
  pthread_t thing1, thing2;

  pthread_create(&thing1, NULL, start_thread, (struct StudentInfor) stu1);
  pthread_create(&thing2, NULL, start_thread, (struct StudentInfor) stu2);

  pthread_join(struct StudentInfor stu1, NULL);
  pthread_join(struct StudentInfor stu2, NULL);

  return 0;
}
