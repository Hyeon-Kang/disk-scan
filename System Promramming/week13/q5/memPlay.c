#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int check = 0;
char board[255]; // 게임 판 저장 (공용자원)

int main(int argc, char* argv[])
{
    //srand(time(NULL));

    // 필요 변수 선언
    int cnt_p, cnt_c = 0; // p, c 카운트 변수
    pid_t pid; // pid 저장
    char path[] = "./";
    strcat(path, argv[1]);

    // 게임판 불러오기 (파일 읽기)
    FILE *pFile = NULL;
    pFile = fopen( path, "r" );

    if( pFile != NULL )
    {
        char *pStr = fgets( board, sizeof(board), pFile ); // 텍스트 한 줄씩 읽어옴
        printf( "배열 검사 : %s\n", board );
        fclose( pFile );
    }
    else
    {
        //에러 처리
        printf("게임판 열기 오류!");
        exit(1);
    }

    if((pid = fork()) > 0) { // 부모 프로세스
        srand(time(NULL));
        for(int i =0; i<100; i++) {
            int random = rand() % 100; // 1~100 범위의 랜덤 값 생성
            //printf("====== 부모 스레드 ======\n");
            printf("부모 스레드 %d 번 값에접근\n", random);
            //printf("%d 번 값 : %c\n", random, board[random]);
            if(board[random] == 'p'){
                //printf("변경하지 않음\n");
            } else {
                printf("부모 스레드가 %d 번 값 변경\n", random);
                board[random] = 'p';
            }
            //printf("\n\n");
            sleep(1);
        } // end for

        sleep(1);

        // 게임 결과 확인
        printf("결과 : %s\n", board);
        // 결과 파일 작성
        FILE *fp = fopen("./result.txt", "w");
        fwrite(board, strlen(board), 1, fp);
        fclose(fp);
        return 0;

    } else if(pid == 0) {
        for(int i=0; i<100; i++) {
            int random = rand() % 100; // 1~100 범위의 랜덤 값 생성
            //printf("====== 자식 스레드 ======\n");
            printf("자식 스레드 %d 번 값에접근\n", random);
            //printf("%d 번 값 : %c\n", random, board[random]);

            if(board[random] == 'c'){
                //printf("변경하지 않음\n");
            } else {
                printf("자식 스레드가 %d 번 값 변경\n", random);
                board[random] = 'c';
            }
            //printf("\n\n");
            sleep(1);
        } // end for
    }
    // return 0;
}
