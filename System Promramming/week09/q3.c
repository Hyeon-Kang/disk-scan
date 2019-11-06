// 호스트명으로 IP 주소 읽어오기


#include <stdio.h>
#include <netdb.h>

int main(int argc, char*argv[]) {
          struct hostent *host;

          sethostent(0);

          host = gethostbyname(argv[1]);
          printf("host name : %s, host IP addr : %s\n", host->h_name, host->h_addr)

          endhostent();
}
