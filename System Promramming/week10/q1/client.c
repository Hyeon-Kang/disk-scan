#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9001 // 서버측 포트 번호

int main(void) {
      int sd;
      char buf[256];
      struct sockaddr_in sin;

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
            perror("connect");
            exit(1);
      }

      // 서버로부터 환영 메시지 받음
      if(recv(sd, buf, sizeof(buf), 0) == -1) {
            perror("recv");
            exit(1);
      }

      // 서버로부터 받은 메시지 출력
      printf("** From Server : %s\n", buf);

      while(1) {
            // 서버로부터 메시지 수신
            if(recv(sd, buf, sizeof(buf), 0) == -1) {
                  perror("recv");
                  exit(1);
            }

            // 서버로부터 받은 메시지 출력
            printf("** From Server : %s\n", buf);

            // 종료 검사
            if (strncmp(buf,"/quit",5) == 0 ){
                  break;
            }

            // 서버로 메시지 전송
            printf("to server : ");
            gets(buf);
            if(send(sd, buf, sizeof(buf) + 1, 0) == -1) {
                  perror("send");
                  exit(1);
            }

            // 종료 검사
            if (strncmp(buf,"/quit",5) == 0 ){
                  break;
            }




      }

      close(sd); // 소켓 기술자 닫기
      return 0;
}
