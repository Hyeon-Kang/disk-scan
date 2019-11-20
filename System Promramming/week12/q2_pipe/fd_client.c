#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

// 서버 프로그램

// 클라이언트는 보내는 메시지에서 <GET> 감지 되면
// 보낸 메시지를 파싱해서 파일 이름 추출

// 클라이언트로부터 메시지를 받으면
// <GET> 감지된 경우 문자열 파싱, 파일 이름 추출
// 추출한 이름으로 파일 읽기모드로 생성
// 클라이언트에게 <RDY> 메시지 전달
// 파일 내용 읽어서 변수에 저장후 디스크립터 닫기

// 클라이언트는 <RDY> 메시지를 감지한다면
// 추출한 파일 이름으로 쓰기모드로 파일 생성
// 다음에 넘어오는 데이터를 쓰고 저장, 디스크립터 닫기


typedef enum {false, true} bool;

#define MAXLINE 256

int readline(int, char *, int); // 한줄씩 읽기 함수

int main (int argc, char * argv[]) {
      int pd, n;
      char inmsg[MAXLINE];
      char sendline[MAXLINE], line[MAXLINE];
      char filename[80];
      pid_t pid;
      int size;

      char *escapechar = "exit\n";	/* 종료문자 */

      //부모 스레드 (client_write 파이프에 쓰기)

      /* 절차 설명
      파이프 생성
      파이프 쓰기모드로 열기
      * 
      터미널 내용에서 개행 입력시 끊어서 문자열 변수로 저장
      저장 변수
      해당 문자열 변수 전송*/

      if( (pid = fork()) > 0) {

            // 파이프 생성
            if(mkfifo("./client_write", 0666) == -1) {
                  perror("fifo 생성 오류");
                  exit(1);
            }

            // 파이프 쓰기모드로 열기
            if((pdw = open("./client_write", O_WRONLY)) == -1) {
                  perror("pipe discriptor 열기 실패");
                  exit(1);
            }


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
