
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
//static sigset_t new;

void handler(int signo) {
    //sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL); // 시그널 집합 new 목록 블로킹 설정
    printf("Nice to meet you!\n");
    //printf("Signal Handler Signal Number : %d\n", signo);
    //psignal(signo, "Recived Signal\n");
    //sigprocmask(SIG_UNBLOCK, &new, (sigset_t *) NULL); // 시그널 집합 목록 블로킹 해제
}
int main(void) {
    struct itimerval it;

    sigset(SIGALRM, handler);
    it.it_value.tv_sec = 1; // 타이머 간격 1초 간격으로 설정
    //it.it_value.tv_usec = 0; // 남은 시간 정보

    if (setitimer(ITIMER_REAL, &it, (struct itimerval *)NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    while(1) {
        alarm(1); // 2초 설정
        sleep(1);
    }

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static sigset_t new;

void handler(int signo) {
    printf("Nice to meet you!\n");
}

int main(void) {
    void(*hand)(int);
    struct itimerval it;
    it.it_value.tv_sec = 1; // 타이머 간격 1초 간격으로 설정
    it.it_value.tv_usec = 0;

    signal(SIGALRM, handler);
    while(1) {
        alarm(1); // 2초 설정
        printf("%d sec, %d msec.\n", (int)it.it_value.tv_sec);
        sleep(1);
    }

    return 0;
}
