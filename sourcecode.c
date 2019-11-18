#include <windows.h>
#include <winbase.h>
#include <stdio.h>

// INTMAX = intmax 값

//#include ST32 NULL    // 4GB 이하
//#include ST64         // 4GB 이상

// 실행 형식 : ./disk_scan (인식 드라이브 경로문자) (읽어올 디스크 용량) (긁어온 데이터 저장 경로)
int main(int argc, char ** argv)
  {
    //bool flag = false; // 출력 검사용 flag
    int retCode = 0;
    BYTE sector[512]; // disk 내용을 읽어올 버퍼 (전통적으로 HDD는 섹터당 512바이트)
    DWORD bytesRead;  // 파일 포인터의 이동 시작 위치를 지정.
    HANDLE device = NULL; // 파일포인터를 옮기고자 하는 대상 파일의 핸들. 목표 저장장치 주소를 담을 변수로 사용.
    int numSector = 5;
    int numSector_high = 5; //up point test

    device = CreateFile("\\\\.\\E:",            // HANDLE 변수에 드라이브 구조체 지정 (경로, 접근 모드, )
                        GENERIC_READ,           // 접근 모드 : 읽기
                        FILE_SHARE_READ,        //|FILE_SHARE_WRITE,(쓰기 옵션은 제거)  // Share Mode
                        NULL,                   // Security Descriptor (default NULL로 설정함)
                        OPEN_EXISTING,          // How to create
                        0,                      // File attributes
                        NULL);                  // Handle to template

    // 32bit 모드
    if(device == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile: %u\n", GetLastError());
        return -1;
    }

/*
    // 64bit 이상 0xFFFFFFFF 분석
    if( (device == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR) ){
      printf("CreateFile: %u\n", GetLastError());
      return 1;
    }
*/
    // 저장장치 용량이 4g보다 크다면 ST64 아니면 ST32
    // 저장장치 용량이 4GB 이하인 경우 3번째 인자는 NULL 값을 주고 2번째 인자로만 파일 위치를 지정한다.
  DWORD dwPos = SetFilePointer (device, numSector*512, NULL, FILE_BEGIN) ; // 32bit clearc


    //DWORD dwPos = SetFilePointer (device, numSector*512, numSector_high*512, FILE_BEGIN) ; // 64bit test

    // 주소 읽어오기
    if (!ReadFile(device, sector, 512, &bytesRead, NULL)) //(장치 핸들러, 읽어올 버퍼, sizeof(버퍼), 읽어온 바이트 수를 반환하기 위한 출력용 인수, 4gb 이하면 null)
    {
        printf("ReadFile: %u\n", GetLastError());
        /*SetFilePointer의 리턴값은 변경된 오프셋 값이며 함수가 실패할 경우에는
        INVALID_SET_FILE_POINTER 를 돌려주게 된다. INVALID_SET_FILE_POINTER의 값은 -1로 정의되어 있고,
        이 값은 DWORD로 받아지기 때문에 0xFFFFFFFF가 된다.
        그런데 만약 내가 변경하고 싶었던 위치가 0xFFFFFFFF(4기가) 였다면?
        사용자는 0xFFFFFFFF위치로 오프셋을 옮겨줄 것을 요청했고
        함수는 사용자가 원한 동작을 제대로 수행한 뒤 0xFFFFFFFF를 리턴했다.
        이제 이 값이 에러인지 정상적인 오프셋 값인지 어떻게 구분해야할까?
        사용자는 이를 확인해보기 위해서 반드시 GetLastError를 호출해야 한다.
        만일 함수가 성공했고 제대로된 오프셋이라면 LastError가 ERROR_SUCCESS로 셋팅되어 있을 것이다.*/
    }


    else
    {
      // 디스크 사이즈 알아낸 다음 나눠서 계속 파일 쓰게 시킴
        // 검증용
        // 16 진수로 바이트 단위로 읽어오기, 점검을 위해 10^9승이 아닌 10^3승까지만 불러옴
        int cnt =0;
        int buf =0;

        // FILE * fp = NULL;
        //
        // fp = fopen("D:\write_test\test.txt", "w+");
        // if(fp == NULL) {
        //       printf("FILE OPEN ERROR!");
        //       exit(0);
        // }

        // 저장장치 용량을 가져와 반복횟수 구현하기
        for(int i=0; i<10000; i++) {
              // sprintf(buf, "%d", sector[i]);
              // if(buf != 0) {
              //       cnt++;
              //       if(cnt>0){
              //             printf("%x",sector[i]);
              //       }
              //
              // }
              printf("%x",sector);
              //fprintf(fp, "%x", sector[i]);
        }

        printf("\nSuccess!\n");

        //fclose(fp);
    }

    // 파일 저장
    return 0;
}

// 지정 경로에 읽어온 데이터를 쓰는 과정 추가, 인식 드라이브 문자 입력
// write file 참조 링크
//https://hh-nn.tistory.com/43
