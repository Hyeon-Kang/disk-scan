#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9005

int main(void) {
      int sd, n;
      char buf[256];
      struct sockaddr_in sin;

      if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket");
            exit(1);
      }

      memset((char *) &sin, '\0', sizeof(sin));
      sin.sin_family = AF_INET; // 인터넷 도메인
      sin.sin_port = htons(PORTNUM);
      sin.sin_addr.s_addr = inet_addr("168.188.54.212");

      strcpy(buf, "<time>");
      if(sendto(sd, buf, strlen(buf)+1, 0, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
            perror("sendto");
            exit(1);
      }

      n = recvfrom(sd, buf, 255, 0, NULL, NULL);
      buf[n] = '\0';
      printf("Server time : %s", buf);

      return 0;
}
