#include <windows.h>
#include <winbase.h>
#include <stdio.h>

// 실행 형식 : ./disk_scan (읽어올 디스크 용량) (긁어온 데이터 저장 경로)
int main(int argc, char ** argv)
  {
    int retCode = 0;
    BYTE sector[512]; // disk 내용을 읽어올 버퍼
    DWORD bytesRead;  // 파일 포인터의 이동 시작 위치를 지정.
    HANDLE device = NULL; // 파일포인터를 옮기고자 하는 대상 파일의 핸들. 목표 저장장치 주소를 담을 변수로 사용.
    int numSector = 5;

    device = CreateFile("\\\\.\\E:",            // HANDLE 변수에 드라이브 구조체 지정 (경로, 접근 모드, )
                        GENERIC_READ,           // 접근 모드 : 읽기
                        FILE_SHARE_READ,        //|FILE_SHARE_WRITE,(쓰기 옵션은 제거)  // Share Mode
                        NULL,                   // Security Descriptor (default NULL로 설정함)
                        OPEN_EXISTING,          // How to create
                        0,                      // File attributes
                        NULL);                  // Handle to template


    if(device == INVALID_HANDLE_VALUE) //
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer (device, numSector*512, NULL, FILE_BEGIN) ;
    // 저장장치 용량이 4GB 이하인 경우 3번째 인자는 NULL 값을 주고 2번째 인자로만 파일 위치를 지정한다.

    // 주소 읽어오기
    if (!ReadFile(device, sector, 512, &bytesRead, NULL)) //(장치 핸들러, 읽어올 버퍼, sizeof(버퍼), 읽어온 바이트 수를 반환하기 위한 출력용 인수, 4gb 이하면 null)
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        // 16 진수로 바이트 단위로 읽어오기, 점검을 위해 10^9승이 아닌 10^3승까지만 불러옴
        for(int i=0; i<1000; i++) {
              printf("%x",sector[i]);
        }

        printf("\nSuccess!\n");
    }

    // 파일 저장
    return 0;
}
