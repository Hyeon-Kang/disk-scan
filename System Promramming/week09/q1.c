// 포트 번호로 서비스 검색하기

#include <netdb.h>
#include <stdlib.h>
// port : 검색할 포트 번호, proto : tcp / udp / NULL

int main(int argc, char*argv[]) {
        struct servent *port;
        int num = atoi(argv[1]);

        //struct servent *getservbyport(num, NULL);
        port = getservbyport(num, NULL);
        printf("Service Name : %s, Port : %d\n", port->s_name, port->s_port);

        endservent();

        return 0;
}
