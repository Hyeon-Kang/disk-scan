/*
‘signal’ 함수를 이용해서 SIGQUIT 시그널 핸들러를 등록하고,
핸들러 호출 시 “SIGQUIT handler is called!”
는 간단한 메시지를 출력하는 프로그램을 작성하세요.
터미널 화면을 캡처해서 본 문서에 첨부하고, 소스코드를 제출하세요.
*/

#include <stdio.h>
#include <stdlib.h>
//#include <siginfo.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo) {
    printf("SIGQUIT handler is called!\n");
    //printf("Signal Handler Signal Number : %d\n", signo);
    psignal(signo, "Recived Signal\n");
}

int main(void) {
    void(*hand)(int);

    hand = signal(SIGQUIT, handler); // 시그널 핸들러 지정
    if (hand == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    printf("Wait Ctrl + \\ : SIGQUIT\n");
    //printf("Wait 1st Ctrl+D... : SIGQUIT\n");
    pause(); // 시그널 입력 대기
    printf("Wait Ctrl + \\ : SIGQUIT\n");
    pause();
    return 0;
}
