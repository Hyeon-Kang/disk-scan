#include <windows.h>
#include <winbase.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    int retCode = 0;
    BYTE sector[512];
    DWORD bytesRead;
    HANDLE device = NULL;
    int numSector = 5;

    device = CreateFile("\\\\.\\E:",    // Drive to open
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
