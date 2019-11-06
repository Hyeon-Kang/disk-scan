#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <time.h>

#define PORTNUM 9005

int main (void) {
      struct tm *tm;
      time_t t;

      time(&t);
      tm = localtime(&t);

      char buf[256];
      struct sockaddr_in sin, cli;
      int sd, clientlen = sizeof(cli);

      // 데이터그램 소켓 생성
      if (( sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket");
            exit(1);
      }

      // 소켓 구조체 설정
      memset((char *) &sin, '\0', sizeof(sin));
      sin.sin_family = AF_INET; // 인터넷 도메인
      sin.sin_port = htons(PORTNUM); // 서버 포트 번호
      sin.sin_addr.s_addr = inet_addr("168.188.54.212"); // 서버 IP 주소

      // 소켓 기술자와 소켓 주소 구조체 연결
      if (bind(sd, (struct sockaddr *) &sin, sizeof(sin))) {
            perror("bind");
            exit(1);
      }


      // 클라이언트 메시지 수신
      if ((recvfrom(sd, buf, 255, 0, \
                    (struct sockaddr *)&cli, &clientlen)) == -1) {
            perror("recvfrom");
            exit(1);
      }
      printf("**From client : %s\n", buf);

      // 클라이언트에게 메시지 송신
      strcpy(buf, asctime(tm));

      if ((sendto(sd, buf, strlen(buf)+1, 0, (struct sockaddr *)&cli,sizeof(cli))) == -1) {
            perror("sendto");
            exit(1);
      }

      return 0;

}
