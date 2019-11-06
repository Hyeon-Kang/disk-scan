#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
//#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define PORTNUM 9002 // 서버측 포트 번호
#define MAXLINE 256

int readline(int, char *, int); // 한줄씩 읽기 함수
char *escapechar = "exit\n";	/* 종료문자 */

int main(void) {
      int sd;
      char buf[256];
      struct sockaddr_in sin;
      char line[MAXLINE], sendline[MAXLINE], recvline[MAXLINE+1];
      pid_t pid;
      int size;

      // 소켓 주소구조체 초기화 및 서버 정보 입력
      memset((char*) &sin, '\0', sizeof(sin));
      sin.sin_family = AF_INET; // 인터네트워크 통신 사용
      sin.sin_port = htons(PORTNUM); // 서버측 포트 번호
      sin.sin_addr.s_addr = inet_addr("168.188.54.212"); // 서버 IP 주소

      // 소켓 생성 (인터넷 도메인, tcp)
      if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
      }

      // 서버에 연결 요청
      if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
            printf("Client : connect error");
            exit(1);
      }

      // 서버로부터 환영 메시지 받음
      if(recv(sd, buf, sizeof(buf), 0) == -1) {
            perror("recv");
            exit(1);
      }

      // 서버로부터 받은 메시지 출력
      printf("** From Server : %s\n", buf);

      // 스레드 수정
      if(( pid = fork()) > 0) {
        /* 부모 프로세스는 키보드 입력을 서버로 전송 */
        while(readline(0, sendline,MAXLINE) != 0) {
          size = strlen(sendline);
          if(write(sd, sendline, strlen(sendline)) != size) {
            printf("Client: can't write to server.\n");
            return -1;
          }
          /* 종료문자열 입력 처리 */
          if(strncmp(sendline, escapechar, 4) == 0) {
            printf("close chat_server.\n");
            kill(pid, SIGQUIT);
            break;
          }
        }
      } else if (pid == 0) {
        /* 자식 프로세스는 소켓으로부터 들어오는 메시지를 화면에 출력 */
        while(1) {
          if((size = read(sd, recvline, MAXLINE)) > 0) {
            recvline[size] = '\0';
            /* 종료문자열 수신시 종료 */
            if(strncmp(recvline, escapechar,4) == 0) break;
            printf("YOU: ");
            printf("%s", recvline);
          }
        }
      }

      close(sd); // 소켓 기술자 닫기
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
