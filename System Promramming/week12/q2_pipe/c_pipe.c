
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define MAXLINE 256

int readline(int, char *, int); // 한줄씩 읽기 함수

int main (int argc, char * argv[]) {
  int pd, n;
  char inmsg[MAXLINE];
  char sendline[MAXLINE], line[MAXLINE];
  pid_t pid;
  int size;

  char *escapechar = "exit\n";	/* 종료문자 */

  // 부모의 경우
  if(( pid = fork()) > 0) {
        // send

        // 클라이언트가 작성할 파이프 생성
        // if(mkfifo("./client_write", 0666) == -1) {
        //       perror("mkfifo");
        //       exit(1);
        // }

        if ((pd = open("./client_write", O_WRONLY)) == -1) {
              perror("open");
              exit(1);
        }

        while(readline(0, sendline, MAXLINE) != 0) { // 표준 입력 가져오기
              size = strlen(sendline);
              // 이름 추가
              sprintf(line, "%s %s", argv[1], sendline);

              n = write(pd, line, strlen(line)+1);
              if (n == -1) {
                    perror("write");
                    exit(1);
              }
              // d이름추가 끝
              // if(write(ns, sendline, strlen(sendline)) != size) {
              //   printf("Server: fail in writing\n");
              // }
              /* 종료 문자열 입력 확인 */
              if(strncmp(sendline, escapechar, 4) == 0) {
                printf("close chat_server.\n");
                close(pd);
                kill(pid, SIGQUIT);
                break;
              }
        }


        //close(pd);

  } else { // 자식의 경우
              // receive
              if ((pd = open ("./server_write", O_RDONLY)) == -1) { // 서버에서 생성한 FIFO 열기
                    perror("open");
                    exit(1);
              }
              //printf("Client =====\n");
              //write(1, "From Servver :", 13);

              while ((n = read(pd, inmsg, MAXLINE)) > 0) // 서버가 보낸 데이터 읽기
                    write(1, inmsg, n);

              if (n == -1) {
                    perror("read");
                    exit(1);
              }
              write(1, "\n", 1);
              close(pd);
        }
        return 0;
}

int readline(int fd, char *ptr, int maxlen) {
  int n, rc;
  char c;
  for(n = 1; n < maxlen; n++) {
    if((rc = read(fd, &c, 1)) == 1) {
      *ptr++ = c;
      if (c == '\n') break;
    } else if (rc == 0) {
      if(n == 1) return (0);
      else break;
    }
  }
  *ptr = 0;
  return (n);
}

// 전송계획 변경!!
// <GET> 식별 후 파일 열고 준비가 끝났다면 클라이언트에게 <RDY> 텍스트를 보낸다.
// 클라 역시 대기하다가 <RDY> 감시하다 인식하면 입력한 파일 이름으로 파일 작성하고
// 받은 텍스트 데이터를 작성하여 저장한다.
