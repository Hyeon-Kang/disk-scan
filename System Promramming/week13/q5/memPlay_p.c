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
        for(int i =0; i<100; i++) {
            FILE *pFile = NULL;
            pFile = fopen( path, "r" );

            if( pFile != NULL )
            {
                fgets( board, sizeof(board), pFile ); // board에 게임판 저장
            }
            fclose( pFile );

            // 게임판에서 c 찾아서 변환
            for(int j =0; j<100; j++) {
                if(board[j] == 'c') {
                    // 게임판 열기
                    FILE *fp = fopen(path, "r+");    // 파일을 읽기/쓰기 모드로 열기.
                    fseek(fp, j, SEEK_SET);
                    printf("부모 스레드 %d 번 값에접근\n", j);
                    fwrite(pp, strlen(pp), 1, fp);
                    rewind(fp);
                    fclose(fp);
                    break;
                }
            }
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
