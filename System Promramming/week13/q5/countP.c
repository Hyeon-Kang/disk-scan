#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argvp[]) {
    char board[255] = {NULL,}; // 게임 판 저장
    int cnt_c, cnt_p = 0; // 카운트 변수

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

    for(int i=0; i<100; i++) {
        if(board[i] == 'p') {
            cnt_p++;
        } else {
            cnt_c++;
        }
    } // end for

    if(cnt_p > cnt_c) {
        printf("Parent won!\n");
    }else if( cnt_p == cnt_c ) {
        printf("Even!\n")
    } else {
        printf("Child won!\n");
    }

}
