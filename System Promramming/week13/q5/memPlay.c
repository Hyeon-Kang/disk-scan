#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int check = 0;
char board[255]; // 게임 판 저장 (공용자원)

int main(int argc, char* argv[])
{
    char cc[] = "c";
    char pp[] = "p";

    pid_t pid; // pid 저장
    char path[] = "./";
    strcat(path, argv[1]);

    if((pid = fork()) > 0) { // 부모 프로세스
        srand(time(NULL)); // 자식과 달리 부모는 가변적 랜덤시드 생성

        for(int i =0; i<100; i++) {
            int random_p = rand() % 100; // 1~100 범위의 랜덤 값 생성

            // 게임판 열기
            FILE *fp = fopen(path, "r+");    // 파일을 읽기/쓰기 모드로 열기.
            fseek(fp, random_p, SEEK_SET);
            printf("부모 스레드 %d 번 값에접근\n", random_p);
            fwrite(pp, strlen(pp), 1, fp);
            rewind(fp);
            fclose(fp);

            sleep(1);
        } // end for
    } else if(pid == 0) {
        for(int j=0; j<100; j++) {
            int random_c = rand() % 100; // 1~100 범위의 랜덤 값 생성
            FILE *fp = fopen(path, "r+");    // 파일을 읽기/쓰기 모드로 열기.
            fseek(fp, random_c, SEEK_SET);
            printf("자식 스레드 %d 번 값에접근\n", random_c);
            fwrite(cc, strlen(cc), 1, fp);
            rewind(fp);
            fclose(fp);

            sleep(1);
        } // end for

    }
    return 0;
}
