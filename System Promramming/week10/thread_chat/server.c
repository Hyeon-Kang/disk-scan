#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9001 // 통신에 사용할 포트 번호 선언

int main (void) {
      char buf[256];
      struct sockaddr_in sin, cli;
      int sd, ns, clientlen = sizeof(cli);

      // 소켓 주소 구조체 초기화 및 값 설정
      memset( (char *) &sin, '\0', sizeof(sin));
      sin.sin_family = AF_INET; // 인터네트워크 통신 소켓 사용
      sin.sin_port = htons(PORTNUM); // 서버 접근 포트
      sin.sin_addr.s_addr = inet_addr("168.188.54.212"); // 서버 IP 주소
      // loop back ip로 할까?

      // 소켓 생성(아직 데이터 안 들어감)
      if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
      }

      // 위에서 지정한 IP 및 포트번호를 소켓에 연결
      if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
            perror("bind");
            exit(1);
      }

      // 클라이언트 접속을 기다림
      // (클라이언트 요청 받을 준비가 되었음을 운영체제에 알림)
      if (listen(sd, 5) == -1) {
            perror("listen");
            exit(1);
      }

      // 클라이언트 접속 허가
      if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
            perror("accept");
            exit(1);
      } // 새로운 소켓 기술자 리턴

      // 클라이언트 주소 출력 (상대방 주소 출력)
      sprintf(buf, "%s", inet_ntoa(cli.sin_addr));
      printf("** 새로운 호스트 접속 : %s\n", buf);

      strcpy(buf, "Welcome to Network Server!");

      // 클라이언트에게 환영 메시지 전송
      if(send(ns, buf, strlen(buf) +1, 0) == -1) {
            perror("send");
            exit(1);
      }


      while (1) { // 서버는 무한 반복으로 서비스 제공



            // 클라이언트로부터 메시지 수신
            if(recv(ns, buf, strlen(buf), 0) == -1) {
                  perror("recv");
                  exit(1);
            }
            // 클라로부터 받은 메시지 출력
            printf("** From Client : %s \n", buf);

            if (strncmp(buf,"/quit",5) == 0 ){
                  printf("통신 종료\n");
                  break;
            }

            // 클라이언트로 메시지 전송
            printf("to Client : ");
            gets(buf);
            if(send(ns, buf, sizeof(buf) + 1, 0) == -1) {
                  perror("send");
                  exit(1);
            }

            printf("\n");
      }
      close(ns); // 서비스가 끝났으므로 소켓 닫기
      close(sd); // 접속 받는 용도로 사용한 소켓 닫기 (서버측)

      return 0;
}
