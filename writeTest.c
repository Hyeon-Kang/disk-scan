#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <string.h>
#include <time.h> // 실행시간 측정

#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#define MAX_LINE 512
/* 구현 방법
1. 디스크 루트로 이동하여 파일리스트 보여주기
2. 지정 파일 삭제 {
파일 이름, 사이즈를 외부에 임시저장 *** 파일의 오프셋 위치를 미리 알 수 없을까?? 혼자면 몰라도 여러 파일이면 좀....
** 파일 사이즈 얻기 GetFileSize https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesize
파일 삭제
}
링크 : 파일의 사이즈 구하기 https://m.blog.naver.com/PostView.nhn?blogId=iloveembla&logNo=220963358032&proxyReferer=https%3A%2F%2Fwww.google.com%2F
2. */

// 실행 형식 : ./disk_scan (인식 드라이브 경로문자) (긁어온 데이터 저장 경로)


void device_scan(char drive_name, char * save_path);

int main(int argc, char * argv[]) {
    time_t start, end; // 실행시간 측정
    double result;   // 실행시간 측정
    int i, j;    // 실행시간 측정
    int sum = 0; // 실행시간 측정

    char make_path[20] = "\\\\.\\";
    strcat(make_path, argv[1]);
    strcat(make_path, ":");


    // test make_path
    printf("test make_path : %s\n", make_path);

    // 나중엔 argv[2]에 저장경로 받아다 사용할 것
    char * save_path = "D:\00 Git desktop\disk-scan";

    start = time(NULL); // 시간 측정 시작

    device_scan(make_path, save_path);

    end = time(NULL); // 시간 측정 끝
    result = (double)(end - start);
    printf("%f", result); //결과 출력
    return 0;
}

void device_scan(char drive_name, char * save_path) {
    int retCode = 0;
    BYTE sector[512]; // disk 내용을 읽어올 버퍼 (전통적으로 HDD는 섹터당 512바이트)
    DWORD bytesRead;  // 파일 포인터의 이동 시작 위치를 지정.
    HANDLE device = NULL; // 파일포인터를 옮기고자 하는 대상 파일의 핸들. 목표 저장장치 주소를 담을 변수로 사용.
    int numSector = 5;
    int numSector_high = 5; //up point test
    BOOL brrtv;

    int iter_cnt =0;

    device = CreateFile("\\\\.\\E:",            // HANDLE 변수에 드라이브 구조체 지정 (경로, 접근 모드, )
    GENERIC_READ,           // 접근 모드 : 읽기
    FILE_SHARE_READ,        //|FILE_SHARE_WRITE,(쓰기 옵션은 제거)  // Share Mode
    NULL,                   // Security Descriptor (default NULL로 설정함)
    OPEN_EXISTING,          // How to create
    0,                      // File attributes
    NULL);                  // Handle to template

    // 32bit 모드
    if(device == INVALID_HANDLE_VALUE) {
        printf("CreateFile: %u\n", GetLastError());
        //return -1;
        exit(1);
    }

    DWORD dwPos = SetFilePointer (device, numSector*512, NULL, FILE_BEGIN) ; // 32bit clearc

    FILE *fp = fopen("result.txt", "wb");    // hello.txt 파일을 쓰기 모드(w)로 열기.
    while(1)
    {

                                       // 파일 포인터를 반환
        memset((void *)sector, 0x00, MAX_LINE);
        brrtv = ReadFile(device, sector, MAX_LINE-1, &bytesRead, NULL);
        if(brrtv && bytesRead == 0) // ReadFile 함수가 끝에 도달하면 0 반환 brrtv == 0으로도 해보기
        {

            break; // 반복문 탈출 (모두 읽어옴)
        }
        fwrite(sector , sizeof(sector) , 1 , fp);

        //printf("%x", sector);
        iter_cnt++;

        if(iter_cnt%10000 == 0) {
            printf("%d  * 10^4 \n", iter_cnt);
        }
    }
    fclose(fp);
    printf("종료!");

} // end main

// 지정 경로에 읽어온 데이터를 쓰는 과정 추가, 인식 드라이브 문자 입력
// write file 참조 링크
//https://hh-nn.tistory.com/43
