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
     fprintf(fp, "test line\n");
   }

   pclose(fp); // 파이프 닫기

   return 0;
}
