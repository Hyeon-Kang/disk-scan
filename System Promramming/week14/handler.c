/*
‘signal’ 함수를 이용해서 SIGQUIT 시그널 핸들러를 등록하고,
핸들러 호출 시 “SIGQUIT handler is called!”
는 간단한 메시지를 출력하는 프로그램을 작성하세요.
터미널 화면을 캡처해서 본 문서에 첨부하고, 소스코드를 제출하세요.
*/

#include <stdio.h>
#include <stdlib.h>
#include <siginfo.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo) {
    printf("SIGQUIT handler is called!");
    psignal(signo, "Recived Signal");
}

int main(void) {
    void(*hand)(int);

    hand = signal(SIGINT, handler); // 시그널 핸들러 지정
    if (hand == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    printf("Wait 1st Ctrl+D... : SIGQUIT\n");
    pause(); // 시그널 입력 대기

    return 0;
}


ssh-rsa AAAAB3NzaC1yc2EAAAABJQAAAQEArvjKXkjFBBfQkLWnrPvNhIiymi7cpOAzyLuND5RQaERdK+neUUUroHz+P0CN1iFGZGt/IP4E20s/nEXmTg6tkqgX4jAM5FZ4VMxMshmKXvrHypraC2Sxf60gAdbaGGzTjsyvESPUjmza2ydH7s72gX8c07YAT1NT4QXz2uu5TWn4+ePywoguGlAkbm1PbWZT7c1W4ojnOUts1O+M86epry1svqPyVnsCjdV4Ve0JfRDr1lgkQO6mENtNAmA9OP6rAmeDC+FjCYjMPRrzei5OzIPTR6rPauac3agYkP8o68hctlQ5r6D7s8xKlv2US2bOQe4uNqeFHzw8eNq0oELnIQ== google-ssh {"userName":"addwin0107","expireOn":"2019-12-03T10:48:35+0000"}
