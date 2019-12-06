
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static sigset_t new;

void handler(int signo) {
    sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL); // 시그널 집합 new 목록 블로킹 설정
    printf("At handler : Wake Up!\n");
    //printf("Signal Handler Signal Number : %d\n", signo);
    //psignal(signo, "Recived Signal\n");
    sigprocmask(SIG_UNBLOCK, &new, (sigset_t *) NULL); // 시그널 집합 목록 블로킹 해제
}

int main(void) {
    void(*hand)(int);
    
    //sigemptyset(&new);
    //sigaddset(&new, SIGINT); // 시그널 집합에 SIGINT 추가

    sigfillset(&new);
    sigdelset(&new, SIGINT);
    //sigaddset(&new, SIGQUIT);

    //hand = signal(SIGINT, handler); // 시그널 핸들러 지정

    signal(SIGALRM, handler);
    for( int i = 0 ; i < 5 ; i++ ) {
        alarm(2); // 2초 설정
        printf("Pause ...\n");
        pause();
    }
    printf("Bye~\n");

    return 0;
}
