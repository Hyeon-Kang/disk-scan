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

int main(void) {
        int sd, len;
        char buf[256];
        struct sockaddr_un ser;


        // 소켓 주소구조체 초기화 및 서버 정보 입력
        memset((char *) &ser, '\0', sizeof(ser));
        ser.sun_family = AF_UNIX; // 호스트 내부통신 소켓 설정
        strcpy(ser.sun_path, SOCKET_NAME);
        len = sizeof(ser.sun_family) + strlen(ser.sun_path);

        // 클라이언트는 서버로 접속할 소켓 구조체만 필요하므로
        // bind 함수 필요없음

        // 소켓 생성
        if ((sd = socket(AF_UNIX, SOCK_STREAM, 0 )) == -1) {
                perror("socket");
                exit(1);
        }

        while(1) {
        // 서버에 연결 요청 (소켓과 연결 데이터가 담긴 구조체 전달)
        if (connect(sd, (struct sockaddr *)&ser, len) <0) {
                perror("bind(connect?) error");
                exit(1);
        }

        // 서버로부터 환영 메시지 수신 (1)
        if (recv(sd, buf, sizeof(buf), 0) == -1) {
                perror("recv error");
                exit(1);
        }

        printf("** From Server : %s\n", buf); // 서버로 부터 받은 메시지 출력

        printf("to server : ");
        scanf("%s", buf);

        // 서버로 메시지 전송 (2)
        if (send(sd, buf, sizeof(buf)+1, 0) == -1) {
                perror("send error");
                exit(1);
        }

        // ack(3)
        if (recv(sd, buf, sizeof(buf), 0) == -1) {
                perror("recv error");
                 exit(1);
        }
        printf("** From Server : %s\n", buf); // 서버로 부터 받은 메시지 출력


        if(strcmp(buf, "quit")!= 0 ) {
                close(sd);
                break;
        }
        } // end while
        return 0;
}
