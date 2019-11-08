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

void *start_thread(StudentInfor *stud) {
  //int i;
  for(int i =0; i<10; i++) {

  }
}

int main(int argc, char* argv[]) {

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
}
