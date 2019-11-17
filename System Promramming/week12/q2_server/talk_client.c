//출처 : http://jkkang.net/unix/netprg/source/talk_server.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLINE 1024

int readline(int, char *, int );	/* 키보드에서 한 줄씩 읽는 함수 */
char *escapechar = "exit\n";	/* 종료문자 정의 */
int main(int argc, char *argv[]) {
  char line[MAXLINE], sendline[MAXLINE], recvline[MAXLINE+1];
  char *haddr;
  int n, size, comp, port;
  pid_t pid;
  static int s;
  static struct sockaddr_in server_addr;
  /* 명령문 입력 인자 처리 */
  if (argc < 3) {
    printf("Usage: %s SERVER_ADDRESS TCP_PORT\n", argv[0]);
    return -1;
  } else {
    haddr = argv[1];	/* 토크 서버 주소 */
    port = atoi(argv[2]);	/* 토크 서버의 포트번호 */
  }

  /* 소켓 생성 */
  if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Client: Can't open stream socket.\n");
    return -1;
  } /* server_addr을 '0'으로 초기화 */
  bzero((char *)&server_addr, sizeof(server_addr));
  /* server_addr 세팅 */
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(haddr);
  server_addr.sin_port = htons(port);

  /* 서버에 연결 요청 */
  if(connect(s,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
    printf("Client: can't connect to server.\n");
    return -1;
  }

  if(( pid = fork()) > 0 {
    /* 부모 프로세스는 키보드 입력을 서버로 전송 */
    while(readline(0, sendline,MAXLINE) != 0) {
      size = strlen(sendline);
      if(write(s, sendline, strlen(sendline)) != size) {
        printf("Client: can't write to server.\n");
        return -1;
      }
      /* 종료문자열 입력 처리 */
      if(strncmp(sendline, escapechar, 4) == 0) {
        kill(pid, SIGQUIT);
        break;
      }
    }
  } else if (pid == 0) {
    /* 자식 프로세스는 소켓으로부터 들어오는 메시지를 화면에 출력 */
    while(1) {
      if((size = read(s, recvline, MAXLINE)) > 0) {
        recvline[size] = '\0';
        /* 종료문자열 수신시 종료 */
        if(strncmp(recvline, escapechar,4) == 0) break;
        printf("%s", recvline);
      }
    }
  }
  close(s); 


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
