#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME     "test_socket" // Working directory에 임시 소켓파일 생성


// server program
int main(void) {
        char buf[256];
        struct sockaddr_un ser, cli;
        int sd, nsd, len, clen;

        // 유닉스 도메인 소켓 생성
        if (( sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
                perror("socket error");
                exit(1);
        }

        // 소켓 구조체에 값 지정
        memset((char *) &ser, 0, sizeof(struct sockaddr_un));
        ser.sun_family = AF_UNIX; // 호스트 내부통신 (AF_INET : 인터 네트워크 통신)
        strcpy(ser.sun_path, SOCKET_NAME);
        len = sizeof(ser.sun_family) + strlen(ser.sun_path);

        // 소켓 기술자와 소켓 주소 구조체 연결
        if (bind (sd, (struct sockaddr *)&ser, len)) {
                perror("bind error");
                exit(1);
        }

        // 클라이언트 접속 대기
        if (listen(sd, 5) < 0) {
                perror("listen");
                exit(1);
        }

        // 클라이언트 접속 받음
        //printf("Wating ...\n");
        while(1) {
                if ((nsd = accept(sd, (struct sockaddr *) &cli, &clen)) == -1) {
                  // 클라이언트 접속 허가
                        perror ("accept error");
                        exit(1);
                } // 새로운 소켓 기술자가 리턴함

                //sprintf(buf, "%s", inet_ntoa(cli.sin_addr));
                // accept 함수로 얻어낸 클라 주소를 문자열로 변환하여 버퍼에 저장
                //printf("*** Send a Message to Client(%s)\n", buf); // 클라 주소 출력

                strcpy(buf, "Welcome to Network Server!\n");

                // 클라이언트에게 환영 메시지 전송 (1)
                if (send(nsd, buf, strlen(buf)+1, 0) == -1) {
                      perror("send");
                      exit(1);
                }

                while(1) {

                      // 클라이언트로부터 메시지 수신받음 (2)
                      if (recv(nsd, buf, sizeof(buf), 0) == -1) {
                              perror("recv error");
                              exit(1);
                      }

                      printf("*** From to Client : %s\n", buf);

                      strcpy(buf, "Server received the message\n");

                      // ack (3)
                      if (send (nsd, buf, sizeof(buf)+1, 0) == -1) {
                              perror("send error");
                              exit(1);
                      }

                }

                close(nsd);

        } // end while

        close(sd);

        return 0;
}
