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



ex) 2바이트씩 파일 포인터 옮겨가면서 2바이트씩 읽기..

참조 링크 : https://xenostudy.tistory.com/362

static DWORD dwSavedFilePointer = FILE_BEGIN;
SetFilePointer(m_hLogFileHandler, dwSavedFilePointer, NULL, FILE_CURRENT);
// 열기 성공했으니 파일 포인터를 옮기고..
ReadFile(m_hLogFileHandler, testbuff, 2, &dwRead, NULL);
// 위에서 넘겨준 만큼만 읽고..
dwSavedFilePointer+=2;
