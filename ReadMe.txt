목표

<외부 저장장치의 물리적 주소로 접근하여 byte 단위로 정보를 받아오는
탐색 프로그램>


제약조건 : 윈도우 상에서만 돌아감 (window.h, winbase.h 라이브러리 사용)

목표 분할
1. hard sector 접근
2. byte 단위로 읽기 시도
3. 읽어온 데이터를 저장


What would you like to do?
1. Read from disk by index of cylinder/track/sector.
2. Read from disk by index of first byte of file.
3. Find first-byte index of file.
4. Quit.

** 만약 용량 제한이 있을 경우를 대비해 2GB sdcard 구매 경로를 남긴다.
http://www.g9.co.kr/Display/VIP/Index/1646467091?jaehuid=200006432&NaPm=ct%3Dk2d6knds%7Cci%3D89e46f4ab9e75409ce503c8d1170b5ce04507148%7Ctr%3Dslsl%7Csn%3D280455%7Chk%3De6e79f9ba2df8056520a5c1175dd0801bc6472e3


===== 응용 목표 ====
읽어온 데이터를 헤더를 파싱 및 분석하여 하드 포렌식 프로그램 만들기!




작업 일지

1. hard sector 접근법

통상적인 방법으로는 응용프로그램에서 hard disk의 물리적 sector에 접근이
불가능 하도록 시스템에서 제한을 두고 있다.

그러나 윈도우의 경우 window.h, winbase.h 에서 FilePointer 함수와
리소스를 안전하게 관리하기 위한 HANDLE 자료형과 Handle table을 통해
Unsigned int 형으로 구성된 리소스 주소를 관리한다.


[window 운영체제에서 HANDLE을 통해 주소를 관리하는 방법 참조]
*) https://m.blog.naver.com/PostView.nhn?blogId=tipsware&logNo=221065382244&proxyReferer=https%3A%2F%2Fwww.google.com%2F


[윈도우 환경에서 hard disk sector를 다루는 표준안 MS document 참조]
https://social.msdn.microsoft.com/Forums/en-US/d425884e-1548-450d-ac33-24d1f42b50e9/c-code-to-read-the-sectors-on-hard-disk?forum=csharpgeneral
The standard way to read sectors of a hard disk is :

CreateFile
DeviceIoControl with IOCTL_DISK_GET_DRIVE_GEOMETRY
VirtualAlloc
SetFilePointer
ReadFile
VirtualFree
CloseHandle




- 참조 내용
SetFilePointer() 함수
#. 내용
 - 파일 포인터를 원하는 위치로 옮길 때 사용하는 함수 입니다.
 win 32bit에서 파일의 최대 크기는 64bit이기 때문에 파일포인터도 64bit의 범위 내에서 이동할 수 있습니다.
 파일 크기가 4GB이하일 경우 세번째 인수는 null값을 주고 두번째 인수만으로 파일 위치를 지정합니다.

#. 원형
DWORD SetFilePointer(
  HANDLE hFile,
  LONG IDistanceToMove,
  PLONG lpDistanceToMoveHigh,
  DWORD dwMoveMethod
);

#. 파라미터
 - HANDLE hFile: 파일포인터를 옮기고자 하는 대상 파일의 핸들.
 - LONG IDistanceToMove: 파일포인터를 옮길 위치를 지정.
 - PLONG lpDistanceToMoveHigh: 파일의 크기가 4GB이상일 경우 파일 포인터를 옮길 위치를 지정.
 - DWORD dwMoveMethod: 파일 포인터의 이동 시작 위치를 지정.
  -> FILE_BEGIN: 파일의 시작 위치에서부터 파일 포인터를 이동.
  -> FILE_CURRENT: 현재 위치에서 파일 포인터를 이동.
  -> FILE_END: 파일의 끝에서부터 파일 포인터를 이동.


※ 파일 포인터란?
 - 파일에 접근할 때 해당 파일의 위치를 가리키는 것을 File Pointer(이하 FP)라고 합니다. 최초로 파일을 열었을 때 FP는 항상 파일의 선두 위치를 가리키지만 파일을 읽거나 쓰면 그만큼 FP가 자동으로 이동하게 됩니다.



출처: https://irontooth.tistory.com/archive/20100322 [자료찾기 귀찮아 내가 만든 블로그]




2. byte 단위로 읽기

디스크 섹터에서 직접 파일을 읽어올 때에는 FilePointer() 함수를 사용한다.

해당 함수는 seek 함수처럼 시작 포인터를 지정 후 순차적으로 읽어오는 방법을 사용함.

[SetFilePointer 참조 링크]
*) https://irontooth.tistory.com/archive/20100322






ex) 2바이트씩 파일 포인터 옮겨가면서 2바이트씩 읽기..

참조 링크 : https://xenostudy.tistory.com/362

static DWORD dwSavedFilePointer = FILE_BEGIN;
SetFilePointer(m_hLogFileHandler, dwSavedFilePointer, NULL, FILE_CURRENT);
// 열기 성공했으니 파일 포인터를 옮기고..
ReadFile(m_hLogFileHandler, testbuff, 2, &dwRead, NULL);
// 위에서 넘겨준 만큼만 읽고..
dwSavedFilePointer+=2;














==== 응용편 ====

파일종류의 판별을 위한 시그니처 분석
http://forensic-proof.com/archives/300




==== 참조 자료 ====

*) GetLastError() 코드 모음
http://egloos.zum.com/sakula99/v/2969627

*) C++ 을 사용한 disk sector 접근 참고 자료
http://www.cplusplus.com/forum/windows/18019/

*) C 포렌식 툴 프로젝트
https://nextline.tistory.com/92

*) Read sectors from hard drive (생각보다 좋음)
http://www.rohitab.com/discuss/topic/17877-read-sectors-from-hard-drive/

*) DeviceIoControl MS document
https://docs.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol?redirectedfrom=MSDN


==== 키워드 정리 ====
reading disk sectors in c
