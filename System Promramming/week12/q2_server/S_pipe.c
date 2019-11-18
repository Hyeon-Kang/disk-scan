#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void) {
      int pd, n;
      char msg[] = "Hello, FIFO";

      printf("Server ==== \n");

      if(mkfifo("./HAN-FIFO", 0666)) == -1) {
            perror("mkfifo");
            exit(1);
      }

      if ((pd = open("./HAN-FIFO", O_WRONLY)) == -1)
}


자식 fork
부모인 경우 쓰기모드로 Open
자식인 경우 읽기모드로 Open
