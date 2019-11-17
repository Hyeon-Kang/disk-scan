#include <stdlib.h>
#include <stdio.h>

int main(void) {
  FILE *fp;
  int a;
   fp = popen("wc -l", "w"); // 파이프 통신을 위한 FILE 포인터 획득
   if(fp == NULL) {
     fprintf(stderr, "peopn failed\n");
     exit(1);
   }

   for (a =0; a<100; a++) {
     fprintf(fp, "test line\n");  //자식 프로세스에 연결된 파이프(fp)로 출력 => wc –l 명령에 100줄의 문자열을 전달
   }
   pclose(fp); // 파이프 닫기
   return 0;
}
