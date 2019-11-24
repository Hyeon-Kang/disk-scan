#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

char board[100] = {NULL,}; // 게임 판 저장(공용자원)
int check = 0;

int main(int argc, char* argv[])
{
    srand(time(NULL));

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
        // char strTemp[1];
		char strTemp[255]; // 1로 제한해볼까?
		char *pStr;

		// while( !feof( pFile ) )   ** 읽기 성공
        for(int i=0; i<100; i++)
		{
			pStr = fgets( strTemp, sizeof(strTemp), pFile ); // 텍스트 한 줄씩 읽어옴
            board[i] = strTemp[0]; // 배열에 게임판 저장
			//printf( "%s", strTemp );
            // printf("%c", pStr)
            //printf( "%s", pStr );
		}
		fclose( pFile );
	}
	else
	{
		//에러 처리
        printf("게임판 열기 오류!");
        exit(1);
	}

    // 배열 저장 검사 (잘 나옴!)
    /*for(int i = 0; i<20; i++) {
        printf("%c\n", board[i]);
    }*/
    if((pid = fork()) > 0) { // 부모 프로세스
        for(int i =0; i<20; i++) {
            int random = rand() % 101; // 1~100 범위의 랜덤 값 생성
            printf("====== 부모 스레드 ======\n");
            printf("부모 스레드 %d 번 값에접근\n", random);
            printf("%d 번 값 : %c", random, board[random]);

            if(board[random] == 'p'){
                printf("변경하지 않음\n");
            } else {
                board[random] = 'p';
            }
            printf("\n\n");
            sleep(1);
        } // end for
    } else if(pid == 0) {
        for(int i=0; i<20; i++) {
            int random = rand() % 101; // 1~100 범위의 랜덤 값 생성
            printf("====== 자식 스레드 ======\n");
            printf("자식 스레드 %d 번 값에접근\n", random);
            printf("%d 번 값 : %c", random, board[random]);

            if(board[random] == 'c'){
                printf("변경하지 않음\n");
            } else {
                board[random] = 'c';
            }
            printf("\n\n");
            sleep(1);
        } // end for
    } // end child

    /*
    if(check == 0) {
        ++check;
        printf ("게임 종료\n");
        // 배열 저장 검사 (잘 나옴!)
        for(int i = 0; i<10; i++) {
            printf("%c\n", board[i]);
        }
    }*/

    FILE *fp = open("result.txt", "w+");
    fprintf("")



	return 0;
}



/*
100칸짜리 char 배열 생성 o
파일 읽기 o
파일 읽으며 p, c 개수 카운트 하기, 배열 칸마다 저장 (offset 1칸만 끌어 써야 하나? 혹은 fread 1 offset 놓고 여러번 반복하면 어떨까?)
자식 스레드 생성

* 자식 스레드 기준
random(1~100 을 돌리며 if ( strcmp(arr[random], "c") != 0 ) 배열을 c로 변환
sleep(1);

물론 부모는 반대로

결과 합산
해당 배열을 파일에 새로 쓰기 strcat(arr[i], "\n");
배열 반복하면서 c, p 개수 카운트 하여 더 높은 쪽 승리!

자식이 절대 승리하는 케이스는

자식이 배열에 접근하기 전 반복으로 스캔하여 p 인 것 부터 접근*/
