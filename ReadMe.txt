목표

<외부 저장장치의 물리적 주소로 접근하여 byte 단위로 정보를 받아오는
탐색 프로그램>


제약조건 : 윈도우 상에서만 돌아감 (window.h, winbase.h 라이브러리 사용)

목표 분할
1. hard sector 접근
2. byte 단위로 읽기 시도
3. 읽어온 데이터를 저장

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
