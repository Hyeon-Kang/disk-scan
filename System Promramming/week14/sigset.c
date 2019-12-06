#include <stdio.h>
#include <signal.h>

int main(void) {
    sigset_t st;

    sigemptyset(&st); // 시그널 집합 0으로 초기화

    sigaddset(&st, SIGINT);
    sigaddset(&st, SIGBUS);

    if (sigismember(&st, SIGBUS)) {// SIGBUS가  설정되었는지 확인
        printf("SIGBUS is setting.\n");
    }

    //printf("** Bit Pattern: %x\n", st.__sigbits[0]);

    return 0;
}
