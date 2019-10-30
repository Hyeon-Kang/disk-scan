#include <windows.h>
#include <winbase.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    int retCode = 0;
    BYTE sector[512];
    DWORD bytesRead;  // 파일 포인터의 이동 시작 위치를 지정.
    HANDLE device = NULL; // 파일포인터를 옮기고자 하는 대상 파일의 핸들. 목표 저장장치 주소를 담을 변수로 사용.
    int numSector = 5;

    device = CreateFile("\\\\.\\E:",    // HANDLE 변수에 드라이브 구조체 지정 (경로, 접근 모드, )
                        GENERIC_READ,           // 접근 모드 : 읽기
                        FILE_SHARE_READ|FILE_SHARE_WRITE,        // Share Mode
                        NULL,                   // Security Descriptor
                        OPEN_EXISTING,          // How to create
                        0,                      // File attributes
                        NULL);                  // Handle to template

    if(device == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer (device, numSector*512, NULL, FILE_BEGIN) ;
    // 저장장치 용량이 4GB 이하인 경우 3번째 인자는 NULL 값을 주고 2번째 인자로만 파일 위치를 지정한다.

    // 주소 읽어오기
    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }

    return 0;
}
