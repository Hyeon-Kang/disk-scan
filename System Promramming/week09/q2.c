// 서비스 명으로 포트 조회
#include <netdb.h>
#include <stdlib.h>
// 서비스명으로 정보 검색: getservbyneme(3)

int main(int argc, char*argv[]) {
        struct servent *port;
        port = getservbyname(argv[1], NULL);
        printf("Service Name : %s, Port : %d\n", port->s_name, port->s_port);
        endservent();
        return 0;
}
