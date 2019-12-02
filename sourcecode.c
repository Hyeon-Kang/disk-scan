#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <string.h>
#include <time.h> // 실행시간 측정

#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#define MAX_LINE 512

void device_scan(char * drive_name);

int main(void) {
    time_t start, end; // 실행시간 측정
    double result;   // 실행시간 측정
    int i, j;    // 실행시간 측정
    int sum = 0; // 실행시간 측정
    char  c1[2];

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("disk_scanner Ver0.2\n\n\n");
    printf("please check your disk space before running this program\n\n");
    printf("Enter the drive symbol.\n");
    printf(" ex) if your drive disk symbol is E:, please enter enter E.\n\n");
    printf("Drive Symbol : ");
    scanf("%s", &c1);
    char make_path[20] = "\\\\.\\";
    strcat(make_path, c1);
    strcat(make_path, ":");


    // test make_path
    printf("test make_path : %s\n", make_path);

    start = time(NULL); // 시간 측정 시작

    device_scan(make_path);

    end = time(NULL); // 시간 측정 끝
    result = (double)(end - start);
    printf("%f", result); //결과 출력
    return 0;
}

void device_scan(char * drive_name) {
    int retCode = 0;
    BYTE sector[MAX_LINE]; // disk 내용을 읽어올 버퍼 (전통적으로 HDD는 섹터당 512바이트)
    DWORD bytesRead;  // 파일 포인터의 이동 시작 위치를 지정.
    HANDLE device = NULL; // 파일포인터를 옮기고자 하는 대상 파일의 핸들. 목표 저장장치 주소를 담을 변수로 사용.
    int numSector = 5;
    int numSector_high = 5; //up point test
    BOOL brrtv;


    device = CreateFile(drive_name,            // HANDLE 변수에 드라이브 구조체 지정 (경로, 접근 모드, )
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

    DWORD dwPos = SetFilePointer (device, numSector*MAX_LINE, NULL, FILE_BEGIN) ; // 32bit clearc

    //FILE *fp = fopen("result.txt", "wb");    // hello.txt 파일을 쓰기 모드(w)로 열기.

    FILE *pFile = NULL;
    pFile = fopen( "./result.txt", "w+t" );

    //for (long j = 0; j<8388608; j++)
    while(1)
    {
        int temp = 0;
        memset((void *)sector, 0x00, 0xFF);
        brrtv = ReadFile(device, sector, MAX_LINE , &bytesRead, NULL);
        //if(brrtv && bytesRead == 0) // ReadFile 함수가 끝에 도달하면 0 반환 brrtv == 0으로도 해보기
        if(brrtv && bytesRead  == 0)
        {
            break; // 반복문 탈출 (모두 읽어옴)
        }
        //fwrite(&sector , sizeof(sector) , 1 , pFile);
        fprintf(pFile, "%s", sector);

        //fwrite(temp , sizeof(temp) , 1 , pFile);
        //fputs(temp, pFile);

    }
    //fclose(fp);
    fclose( pFile );
    printf("스캔 완료!");

} // end main
